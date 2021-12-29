WORKING_DIR=src/metal

swiftc -framework Foundation -framework Cocoa -framework MetalKit -framework Metal src/metal/AppDelegate.swift $WORKING_DIR/MiCore/Engine.swift -o Test && ./Test
