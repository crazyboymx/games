#!python
import os,re,sys,commands

# 'MainLayer', 'MainScene', "GameController", "Drop", "InformationLayer", \
# 	"LevelConfiguration", "GameOverLayer"

for module in sys.argv[1:]:
	# print '#include "%s.h"' % module
	f = open(module + '.h', 'w')
	f.write("""
#ifndef __PINGANY_%s_H__
#define __PINGANY_%s_H__

class %s : public CCObject
{
	%s(){}
	bool init(){ return true; }
public:
	~%s(){}
	CREATE_FUNC(%s);
};

#endif
"""%( module.upper(), module.upper(), module, module, module, module));
	f.close();

	f = open(module + '.cpp', "w")
	f.write("""
#include "pch.h"
#include "project.h"
""")
	f.close();

	commands.getoutput("git add %s.h %s.cpp" % (module, module))

