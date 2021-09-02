FROM amazonlinux:2
WORKDIR /app
RUN yum install -y clang
ADD httplib.h .
ADD main.cpp .
ADD test/server.cpp .
RUN clang++ -std=c++20 -Oz -fno-rtti -fno-stack-protector -fno-ident -fmerge-all-constants main.cpp -o main && strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag main
RUN clang++ -std=c++20 -pthread -o3 -s server.cpp -o server
ENTRYPOINT /app/main
