docker build --platform linux/amd64 -t aws-lambda-cpp-mongodb .
docker create -ti --name build-the-program aws-lambda-cpp /bin/bash
mkdir -p bin
docker cp build-the-program:/app/main ./bootstrap
docker rm -f build-the-program
rm -f bootstrap.zip
zip bootstrap bootstrap
