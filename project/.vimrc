set ts=2 sw=2

function CMake()
  wa
  !(rm CMakeCache.txt)
  !(cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug .)
endfunction

function Make()
  wa
  !(cmake --build . -- -j 3 |& tee MSG.txt)
endfunction

function Run()
  !(./main)
endfunction

function MakeRun()
  wa
  !(cmake --build . -- -j 3 |& tee MSG.txt) && (./main)
endfunction

command! CMake call CMake()
command! Make call Make()
command! Run call Run()
command! MakeRun call MakeRun()

autocmd User NERDTreeInit global/src/normal o

