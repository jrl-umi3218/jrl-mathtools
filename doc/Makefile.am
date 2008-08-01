# 
#  Copyright 2008 AIST-CNRS 
#  Author Florent Lamiraux
# 


jrlMathToolsdir = $(datadir)/doc/jrlMathTools

EXTRA_DIST = \
	header.html \
	footer.html \
	package.css \
	pictures/footer.jpg \
	additionalDoc/package.h 


install:html-doc 
	mkdir -p $(jrlMathToolsdir)
	$(INSTALL_DATA) html/* $(jrlMathToolsdir)
	mkdir -p $(jrlMathToolsdir)/pictures
	$(INSTALL_DATA) $(srcdir)/pictures/* $(jrlMathToolsdir)/pictures
	mkdir -p $(datadir)/doc/doxytag
	$(INSTALL_DATA) jrlMathTools.doxytag $(datadir)/doc/doxytag

html-doc: package.dox
	doxygen $<
