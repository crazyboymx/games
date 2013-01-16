#!python
import os,re,sys,commands

# 'MainLayer', 'MainScene', "GameController", "Drop", "InformationLayer", \
# 	"LevelConfiguration", "GameOverLayer"

for file in sys.argv[1:]:
	# print '#include "%s.h"' % file
	f = open(file + '.h', 'w')
	f.write("""
#ifndef __PINGANY_%s_H__
#define __PINGANY_%s_H__

#endif
"""%( file.upper(), file.upper()));
	f.close();

	f = open(file + '.cpp', "w")
	f.write("""
#include "pch.h"
#include "project.h"
""")
	f.close();

	commands.getoutputstatus("git add %s.h %s.cpp" % (file, file))

