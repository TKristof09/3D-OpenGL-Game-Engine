function! UpdateCmake()
		call system("../../build.sh Debug 1")
endfunction
function! Build()
        silent :!clear
		execute "cd ../.."
		execute "! ./build.sh"
		execute "cd 3DGameEngine/Engine"
endfunction
function! Run()
		execute "cd ../.."
		call system("./Build/3DGameEngine")
		execute "cd 3DGameEngine/Engine"
endfunction
au FileType cpp call UpdateCmake()
map <F5> :call Build()<CR>
map <C-F5> :call Build() \| :call Run()<CR>
