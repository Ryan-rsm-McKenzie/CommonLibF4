#!/bin/sh

CLANG_FORMAT=clang-format-12

CURRENT_BRANCH="$(git branch --show-current)"

# If this was triggered by a pull request...
if [ -n "$GITHUB_BASE_REF" ]; then
    # Test from the the last commit of base branch to head of pull request
    RANGE="$(git rev-parse $GITHUB_BASE_REF) HEAD"
# Otherwise, if we're not on master, check from the merge base of master
elif [ "$CURRENT_BRANCH" != "master" ]; then
	RANGE="$(git merge-base HEAD master) HEAD"
# Otherwise, check last commit
else
	RANGE=HEAD
fi

echo "Checking $RANGE"
FILES=$(git diff-tree --no-commit-id --name-only -r $RANGE | grep -E "\.(c|h|cpp|hpp|cc|hh|cxx|m|mm|inc)$")
echo "Checking files:\n$FILES"

# create a random filename to store our generated patch
prefix="static-check-clang-format"
suffix="$(date +%s)"
patch="/tmp/$prefix-$suffix.patch"

for file in $FILES; do
    "$CLANG_FORMAT" -style=file "$file" | \
        diff -u "$file" - | \
        sed -e "1s|--- |--- a/|" -e "2s|+++ -|+++ b/$file|" >> "$patch"
done

# if no patch has been generated all is ok, clean up the file stub and exit
if [ ! -s "$patch" ] ; then
    printf "Files in this commit comply with the clang-format rules.\n"
    rm -f "$patch"
    exit 0
fi

# a patch has been created, notify the user and exit
printf "\n*** The following differences were found between the code to commit "
printf "and the clang-format rules:\n\n"
cat "$patch"
printf "\n*** Aborting, please fix your commit(s) with 'git commit --amend' or 'git rebase -i <hash>'\n"
exit 1
