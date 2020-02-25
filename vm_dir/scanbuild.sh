 curl -o checker-279.tar.bz2 https://clang-analyzer.llvm.org/downloads/checker-279.tar.bz2
 tar -jxf checker-279.tar.bz2
 rm -rf checker-279.tar.bz2
 mv checker-279 static_analyzer
 echo "alias scan='$PWD/static_analyzer/bin/scan-build'" >> ~/.zshrc
 source ~/.zshrc
