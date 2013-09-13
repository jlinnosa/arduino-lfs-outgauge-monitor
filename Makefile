indent:
	find . -regex '.*\.\(h\|pde\)' -exec indent -v -kr -i8 '{}' +

install:
	[ -d ~/sketchbook/libraries ] || mkdir -p ~/sketchbook/libraries 
	cp -R sketches/* ~/sketchbook
	cp -R libraries/* ~/sketchbook/libraries
