path=$1
swiftpath=src/MiCore/extern/osxlib/swift

mkdir -p $swiftpath/$path
cd $swiftpath/$path
swift package init