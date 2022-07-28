APPNAME=$1

mkdir -p build/$APPNAME.app/Contents/MacOS
cp -R package/. build/$APPNAME.app/Contents/MacOS
mv build/$APPNAME.app/Contents/MacOS/result build/$APPNAME.app/Contents/MacOS/$APPNAME
chmod +x build/$APPNAME.app/Contents/MacOS/$APPNAME