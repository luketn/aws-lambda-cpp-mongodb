docker build --platform linux/amd64 -t aws-lambda-cpp .
docker-compose up -d server
docker-compose up client
