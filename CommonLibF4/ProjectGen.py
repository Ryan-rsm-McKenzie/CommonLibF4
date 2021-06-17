import os

HEADER_TYPES = (".h", ".hpp", ".hxx")
SOURCE_TYPES = (".c", ".cpp", ".cxx")
ALL_TYPES = HEADER_TYPES + SOURCE_TYPES

def make_header(a_directory, a_filename, a_exclude):
	a_exclude.add(a_filename)

	out = open(a_directory + "/" + a_filename, "w", encoding="utf-8")
	out.write("#pragma once\n")
	out.write("\n")
	out.write('#include "F4SE/Impl/PCH.h"\n')
	out.write("\n")

	tmp = list()
	for dirpath, dirnames, filenames in os.walk(a_directory):
		rem = list()
		for dirname in dirnames:
			if dirname in a_exclude:
				rem.append(dirname)
		for todo in rem:
			dirnames.remove(todo)

		for filename in filenames:
			if filename not in a_exclude and filename.endswith(HEADER_TYPES):
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

def make_cmake():
	tmp = list()
	for dirpath, dirnames, filenames in os.walk("include"):
		for filename in filenames:
			if filename.endswith(ALL_TYPES):
				path = os.path.join(dirpath, filename)
				tmp.append(os.path.normpath(path))

	headers = list()
	sources = list()
	for file in tmp:
		name = file.replace("\\", "/")
		if name.endswith(HEADER_TYPES):
			headers.append(name)
		elif name.endswith(SOURCE_TYPES):
			sources.append(name)

	def do_make(a_filename, a_varname, a_files):
		out = open("cmake/" + a_filename + ".cmake", "w", encoding="utf-8")
		out.write("set({}\n".format(a_varname))

		for file in a_files:
			out.write("\t{}\n".format(file))

		out.write(")\n")

	do_make("headerlist", "HEADERS", headers)
	do_make("sourcelist", "SOURCES", sources)

def main():
	cur = os.path.dirname(os.path.realpath(__file__))
	os.chdir(cur)
	make_cmake()

	os.chdir(cur + "/include")
	make_header("F4SE", "F4SE.h", {"Impl"})
	make_header("RE", "Fallout.h", {"NiRTTI_IDs.h", "RTTI_IDs.h", "VTABLE_IDs.h", "msvc"})

if __name__ == "__main__":
	main()
