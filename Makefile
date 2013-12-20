indent:
	find . -regex '.*\.\(h\|pde\|ino\)' -exec indent -v -kr -i8 '{}' +

install:
	[ -d ~/sketchbook/libraries ] || mkdir -p ~/sketchbook/libraries 
	find `pwd`/sketches -mindepth 1 -maxdepth 1 -type d -exec ln -sf '{}' ~/sketchbook \;
	find `pwd`/libraries -mindepth 1 -maxdepth 1 -type d -exec ln -sf '{}' ~/sketchbook/libraries \;

clean:
	find . -type f -name '*~' -exec rm '{}' \;
