# 
#  Copyright 2008 CNRS-AIST
#  Author: Florent Lamiraux 
# 

SUBDIRS = \
	include \
	doc 

jrlMathToolsdir = $(libdir)/pkgconfig
jrlMathTools_DATA = jrlMathTools.pc

install-data-hook: documentation

documentation:
	cd doc; $(MAKE) install
