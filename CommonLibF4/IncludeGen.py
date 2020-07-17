import os

HEADER_TYPES = (".h", ".hpp", ".hxx")
SOURCE_TYPES = (".c", ".cpp", ".cxx")

def make_f4se_header():
	oldDir = os.getcwd()
	os.chdir("include")

	out = open("F4SE/F4SE.h", "w", encoding="utf-8")
	out.write("#pragma once\n")
	out.write("\n")
	out.write('#include "F4SE/Impl/PCH.h"\n')
	out.write("\n")

	tmp = list()
	for dirpath, dirnames, filenames in os.walk("F4SE"):
		if dirnames.count("Impl") > 0:
			dirnames.remove("Impl")

		for filename in filenames:
			if filename.endswith(HEADER_TYPES) and filename != "F4SE.h":
				path = os.path.join(dirpath, filename)
				tmp.append(os.path.normpath(path))

	files = list()
	for file in tmp:
		files.append(file.replace("\\", "/"))

	files.sort()
	for file in files:
		out.write('#include "')
		out.write(file)
		out.write('"\n')

	os.chdir(oldDir)

def main():
	cur = os.path.dirname(os.path.realpath(__file__))
	os.chdir(cur)

	make_f4se_header()

if __name__ == "__main__":
	main()
