indent:
	indent -kr -i8 *.pde *.h

install:
	[ -d ~/sketchbook/libraries ] || mkdir -p ~/sketchbook/libraries 
	cp -R sketches/* ~/sketchbook
	cp -R libraries/* ~/sketchbook/libraries
