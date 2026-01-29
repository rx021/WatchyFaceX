let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Downloads/0-CLOUD/WatchyFaceX
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +1 README.md
badd +1 WatchyFaceX.ino
badd +1 .gitignore
badd +2 logs.md
badd +1 main.h
badd +1 settings.h
argglobal
%argdel
tabnew +setlocal\ bufhidden=wipe
tabrewind
edit README.md
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 79 + 79) / 158)
exe '2resize ' . ((&lines * 19 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 78 + 79) / 158)
exe '3resize ' . ((&lines * 19 + 21) / 42)
exe 'vert 3resize ' . ((&columns * 78 + 79) / 158)
argglobal
balt logs.md
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
let s:l = 1 - ((0 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify(".gitignore", ":p")) | buffer .gitignore | else | edit .gitignore | endif
if &buftype ==# 'terminal'
  silent file .gitignore
endif
balt WatchyFaceX.ino
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
let s:l = 1 - ((0 * winheight(0) + 9) / 19)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 0
lcd ~/Downloads/0-CLOUD/WatchyFaceX
wincmd w
argglobal
if bufexists(fnamemodify("~/Downloads/0-CLOUD/WatchyFaceX/logs.md", ":p")) | buffer ~/Downloads/0-CLOUD/WatchyFaceX/logs.md | else | edit ~/Downloads/0-CLOUD/WatchyFaceX/logs.md | endif
if &buftype ==# 'terminal'
  silent file ~/Downloads/0-CLOUD/WatchyFaceX/logs.md
endif
balt ~/Downloads/0-CLOUD/WatchyFaceX/.gitignore
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
let s:l = 1 - ((0 * winheight(0) + 9) / 19)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 0
lcd ~/Downloads/0-CLOUD/WatchyFaceX
wincmd w
exe 'vert 1resize ' . ((&columns * 79 + 79) / 158)
exe '2resize ' . ((&lines * 19 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 78 + 79) / 158)
exe '3resize ' . ((&lines * 19 + 21) / 42)
exe 'vert 3resize ' . ((&columns * 78 + 79) / 158)
tabnext
edit ~/Downloads/0-CLOUD/WatchyFaceX/WatchyFaceX.ino
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 79 + 79) / 158)
exe 'vert 2resize ' . ((&columns * 78 + 79) / 158)
argglobal
balt ~/Downloads/0-CLOUD/WatchyFaceX/main.h
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
let s:l = 1 - ((0 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 0
lcd ~/Downloads/0-CLOUD/WatchyFaceX
wincmd w
argglobal
if bufexists(fnamemodify("~/Downloads/0-CLOUD/WatchyFaceX/settings.h", ":p")) | buffer ~/Downloads/0-CLOUD/WatchyFaceX/settings.h | else | edit ~/Downloads/0-CLOUD/WatchyFaceX/settings.h | endif
if &buftype ==# 'terminal'
  silent file ~/Downloads/0-CLOUD/WatchyFaceX/settings.h
endif
balt ~/Downloads/0-CLOUD/WatchyFaceX/main.h
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
let s:l = 1 - ((0 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 0
lcd ~/Downloads/0-CLOUD/WatchyFaceX
wincmd w
exe 'vert 1resize ' . ((&columns * 79 + 79) / 158)
exe 'vert 2resize ' . ((&columns * 78 + 79) / 158)
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
