WORKING_DIR=src/metal
cd $WORKING_DIR
swiftc -framework Foundation -framework Cocoa -framework MetalKit -framework Metal AppDelegate.swift MiCore/Engine.swift -o Test && ./Test
