FILE_NAME=libMi

cd libraries
go build -a && go run $FILE_NAME.go
go build -a -buildmode=c-archive $FILE_NAME.go
cp $FILE_NAME.a libmain.a
rm $FILE_NAME.a && rm $FILE_NAME.h && rm libraries

mv libmain.a ../exported