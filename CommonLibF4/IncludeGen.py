import os

HEADER_TYPES = (".h", ".hpp", ".hxx")
SOURCE_TYPES = (".c", ".cpp", ".cxx")

def make_header(a_directory, a_filename, a_recursive):
	out = open(a_directory + "/" + a_filename, "w", encoding="utf-8")
	out.write("#pragma once\n")
	out.write("\n")
	out.write('#include "F4SE/Impl/PCH.h"\n')
	out.write("\n")

	tmp = list()
	for dirpath, dirnames, filenames in os.walk(a_directory):
		if not a_recursive:
			dirnames.clear()

		for filename in filenames:
			if filename.endswith(HEADER_TYPES) and filename != a_filename:
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

def main():
	cur = os.path.dirname(os.path.realpath(__file__)) + "/include"
	os.chdir(cur)

	make_header("F4SE", "F4SE.h", False)
	make_header("RE", "Fallout.h", True)

if __name__ == "__main__":
	main()
