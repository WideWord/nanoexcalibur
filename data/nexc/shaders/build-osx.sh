shaderc -f source/sprite.vs.sc -o ogl/sprite.vs --platform osx -p 120 --type v
shaderc -f source/sprite.fs.sc -o ogl/sprite.fs --platform osx -p 120 --type f
shaderc -f source/gui.vs.sc -o ogl/gui.vs --platform osx -p 120 --type v
shaderc -f source/gui.fs.sc -o ogl/gui.fs --platform osx -p 120 --type f

shaderc -f source/sprite.vs.sc -o metal/sprite.vs --platform osx -p metal --type v
shaderc -f source/sprite.fs.sc -o metal/sprite.fs --platform osx -p metal --type f
shaderc -f source/gui.vs.sc -o metal/gui.vs --platform osx -p metal --type v
shaderc -f source/gui.fs.sc -o metal/gui.fs --platform osx -p metal --type f