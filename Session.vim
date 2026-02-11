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
badd +16 WatchyFaceX.ino
badd +3 .gitignore
badd +30 logs.md
badd +1 main.h
badd +14 settings.h
badd +1 Images/media.h
badd +1 Faces/media.h
badd +47 hub.h
badd +272 Faces/calendar.h
badd +28 Faces/analog.h
badd +1 Fonts/DIN_1451_Engschrift_Regular12pt7b.h
badd +331 Fonts/Technology18pt7b.h
badd +3 Fonts/Seven_Segment10pt7b.h
badd +2 Icons/wifi.h
badd +2 Icons/wifioff.h
argglobal
%argdel
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabrewind
edit README.md
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
wincmd _ | wincmd |
vsplit
2wincmd h
wincmd _ | wincmd |
split
wincmd _ | wincmd |
split
2wincmd k
wincmd w
wincmd w
wincmd w
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
exe '1resize ' . ((&lines * 11 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 56 + 79) / 158)
exe '2resize ' . ((&lines * 11 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 56 + 79) / 158)
exe '3resize ' . ((&lines * 15 + 21) / 42)
exe 'vert 3resize ' . ((&columns * 56 + 79) / 158)
exe 'vert 4resize ' . ((&columns * 56 + 79) / 158)
exe 'vert 5resize ' . ((&columns * 44 + 79) / 158)
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
let s:l = 79 - ((1 * winheight(0) + 5) / 11)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 79
normal! 012|
wincmd w
argglobal
if bufexists(fnamemodify("README.md", ":p")) | buffer README.md | else | edit README.md | endif
if &buftype ==# 'terminal'
  silent file README.md
endif
balt logs.md
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
let s:l = 66 - ((0 * winheight(0) + 5) / 11)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 66
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("README.md", ":p")) | buffer README.md | else | edit README.md | endif
if &buftype ==# 'terminal'
  silent file README.md
endif
balt logs.md
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
let s:l = 167 - ((2 * winheight(0) + 7) / 15)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 167
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("README.md", ":p")) | buffer README.md | else | edit README.md | endif
if &buftype ==# 'terminal'
  silent file README.md
endif
balt logs.md
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
let s:l = 102 - ((24 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 102
normal! 012|
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
let s:l = 23 - ((12 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 23
normal! 047|
lcd ~/Downloads/0-CLOUD/WatchyFaceX
wincmd w
5wincmd w
exe '1resize ' . ((&lines * 11 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 56 + 79) / 158)
exe '2resize ' . ((&lines * 11 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 56 + 79) / 158)
exe '3resize ' . ((&lines * 15 + 21) / 42)
exe 'vert 3resize ' . ((&columns * 56 + 79) / 158)
exe 'vert 4resize ' . ((&columns * 56 + 79) / 158)
exe 'vert 5resize ' . ((&columns * 44 + 79) / 158)
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
exe '1resize ' . ((&lines * 34 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 84 + 79) / 158)
exe '2resize ' . ((&lines * 34 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 84 + 79) / 158)
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
let s:l = 16 - ((15 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 16
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
let s:l = 1 - ((0 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 0
lcd ~/Downloads/0-CLOUD/WatchyFaceX
wincmd w
exe '1resize ' . ((&lines * 34 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 84 + 79) / 158)
exe '2resize ' . ((&lines * 34 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 84 + 79) / 158)
tabnext
edit ~/Downloads/0-CLOUD/WatchyFaceX/main.h
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd _ | wincmd |
split
wincmd _ | wincmd |
split
2wincmd k
wincmd w
wincmd w
wincmd w
wincmd _ | wincmd |
split
wincmd _ | wincmd |
split
2wincmd k
wincmd w
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
exe '1resize ' . ((&lines * 11 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 84 + 79) / 158)
exe '2resize ' . ((&lines * 11 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 84 + 79) / 158)
exe '3resize ' . ((&lines * 10 + 21) / 42)
exe 'vert 3resize ' . ((&columns * 84 + 79) / 158)
exe '4resize ' . ((&lines * 11 + 21) / 42)
exe 'vert 4resize ' . ((&columns * 84 + 79) / 158)
exe '5resize ' . ((&lines * 11 + 21) / 42)
exe 'vert 5resize ' . ((&columns * 84 + 79) / 158)
exe '6resize ' . ((&lines * 10 + 21) / 42)
exe 'vert 6resize ' . ((&columns * 84 + 79) / 158)
argglobal
balt ~/Downloads/0-CLOUD/WatchyFaceX/WatchyFaceX.ino
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
let s:l = 65 - ((7 * winheight(0) + 5) / 11)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 65
normal! 019|
lcd ~/Downloads/0-CLOUD/WatchyFaceX
wincmd w
argglobal
if bufexists(fnamemodify("~/Downloads/0-CLOUD/WatchyFaceX/main.h", ":p")) | buffer ~/Downloads/0-CLOUD/WatchyFaceX/main.h | else | edit ~/Downloads/0-CLOUD/WatchyFaceX/main.h | endif
if &buftype ==# 'terminal'
  silent file ~/Downloads/0-CLOUD/WatchyFaceX/main.h
endif
balt ~/Downloads/0-CLOUD/WatchyFaceX/WatchyFaceX.ino
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
let s:l = 114 - ((5 * winheight(0) + 5) / 11)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 114
normal! 0
lcd ~/Downloads/0-CLOUD/WatchyFaceX
wincmd w
argglobal
if bufexists(fnamemodify("~/Downloads/0-CLOUD/WatchyFaceX/main.h", ":p")) | buffer ~/Downloads/0-CLOUD/WatchyFaceX/main.h | else | edit ~/Downloads/0-CLOUD/WatchyFaceX/main.h | endif
if &buftype ==# 'terminal'
  silent file ~/Downloads/0-CLOUD/WatchyFaceX/main.h
endif
balt ~/Downloads/0-CLOUD/WatchyFaceX/WatchyFaceX.ino
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
let s:l = 129 - ((0 * winheight(0) + 5) / 10)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 129
normal! 025|
lcd ~/Downloads/0-CLOUD/WatchyFaceX
wincmd w
argglobal
if bufexists(fnamemodify("~/Downloads/0-CLOUD/WatchyFaceX/main.h", ":p")) | buffer ~/Downloads/0-CLOUD/WatchyFaceX/main.h | else | edit ~/Downloads/0-CLOUD/WatchyFaceX/main.h | endif
if &buftype ==# 'terminal'
  silent file ~/Downloads/0-CLOUD/WatchyFaceX/main.h
endif
balt ~/Downloads/0-CLOUD/WatchyFaceX/WatchyFaceX.ino
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
let s:l = 157 - ((4 * winheight(0) + 5) / 11)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 157
normal! 04|
lcd ~/Downloads/0-CLOUD/WatchyFaceX
wincmd w
argglobal
if bufexists(fnamemodify("~/Downloads/0-CLOUD/WatchyFaceX/main.h", ":p")) | buffer ~/Downloads/0-CLOUD/WatchyFaceX/main.h | else | edit ~/Downloads/0-CLOUD/WatchyFaceX/main.h | endif
if &buftype ==# 'terminal'
  silent file ~/Downloads/0-CLOUD/WatchyFaceX/main.h
endif
balt ~/Downloads/0-CLOUD/WatchyFaceX/WatchyFaceX.ino
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
let s:l = 233 - ((5 * winheight(0) + 5) / 11)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 233
normal! 016|
lcd ~/Downloads/0-CLOUD/WatchyFaceX
wincmd w
argglobal
if bufexists(fnamemodify("~/Downloads/0-CLOUD/WatchyFaceX/main.h", ":p")) | buffer ~/Downloads/0-CLOUD/WatchyFaceX/main.h | else | edit ~/Downloads/0-CLOUD/WatchyFaceX/main.h | endif
if &buftype ==# 'terminal'
  silent file ~/Downloads/0-CLOUD/WatchyFaceX/main.h
endif
balt ~/Downloads/0-CLOUD/WatchyFaceX/WatchyFaceX.ino
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
let s:l = 165 - ((5 * winheight(0) + 5) / 10)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 165
normal! 019|
lcd ~/Downloads/0-CLOUD/WatchyFaceX
wincmd w
exe '1resize ' . ((&lines * 11 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 84 + 79) / 158)
exe '2resize ' . ((&lines * 11 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 84 + 79) / 158)
exe '3resize ' . ((&lines * 10 + 21) / 42)
exe 'vert 3resize ' . ((&columns * 84 + 79) / 158)
exe '4resize ' . ((&lines * 11 + 21) / 42)
exe 'vert 4resize ' . ((&columns * 84 + 79) / 158)
exe '5resize ' . ((&lines * 11 + 21) / 42)
exe 'vert 5resize ' . ((&columns * 84 + 79) / 158)
exe '6resize ' . ((&lines * 10 + 21) / 42)
exe 'vert 6resize ' . ((&columns * 84 + 79) / 158)
tabnext
edit ~/Downloads/0-CLOUD/WatchyFaceX/hub.h
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd _ | wincmd |
split
1wincmd k
wincmd w
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
exe '1resize ' . ((&lines * 17 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 84 + 79) / 158)
exe '2resize ' . ((&lines * 16 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 84 + 79) / 158)
exe '3resize ' . ((&lines * 34 + 21) / 42)
exe 'vert 3resize ' . ((&columns * 84 + 79) / 158)
argglobal
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
let s:l = 32 - ((14 * winheight(0) + 8) / 17)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 32
normal! 0
lcd ~/Downloads/0-CLOUD/WatchyFaceX
wincmd w
argglobal
if bufexists(fnamemodify("~/Downloads/0-CLOUD/WatchyFaceX/hub.h", ":p")) | buffer ~/Downloads/0-CLOUD/WatchyFaceX/hub.h | else | edit ~/Downloads/0-CLOUD/WatchyFaceX/hub.h | endif
if &buftype ==# 'terminal'
  silent file ~/Downloads/0-CLOUD/WatchyFaceX/hub.h
endif
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
let s:l = 119 - ((90 * winheight(0) + 8) / 16)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 119
normal! 028|
lcd ~/Downloads/0-CLOUD/WatchyFaceX
wincmd w
argglobal
if bufexists(fnamemodify("~/Downloads/0-CLOUD/WatchyFaceX/hub.h", ":p")) | buffer ~/Downloads/0-CLOUD/WatchyFaceX/hub.h | else | edit ~/Downloads/0-CLOUD/WatchyFaceX/hub.h | endif
if &buftype ==# 'terminal'
  silent file ~/Downloads/0-CLOUD/WatchyFaceX/hub.h
endif
balt ~/Downloads/0-CLOUD/WatchyFaceX/Faces/analog.h
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
let s:l = 92 - ((0 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 92
normal! 019|
lcd ~/Downloads/0-CLOUD/WatchyFaceX
wincmd w
exe '1resize ' . ((&lines * 17 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 84 + 79) / 158)
exe '2resize ' . ((&lines * 16 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 84 + 79) / 158)
exe '3resize ' . ((&lines * 34 + 21) / 42)
exe 'vert 3resize ' . ((&columns * 84 + 79) / 158)
tabnext
edit ~/Downloads/0-CLOUD/WatchyFaceX/Faces/analog.h
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
exe '1resize ' . ((&lines * 34 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 79 + 79) / 158)
exe '2resize ' . ((&lines * 34 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 89 + 79) / 158)
argglobal
balt ~/Downloads/0-CLOUD/WatchyFaceX/Faces/media.h
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
let s:l = 232 - ((20 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 232
normal! 022|
lcd ~/Downloads/0-CLOUD/WatchyFaceX
wincmd w
argglobal
if bufexists(fnamemodify("~/Downloads/0-CLOUD/WatchyFaceX/Faces/analog.h", ":p")) | buffer ~/Downloads/0-CLOUD/WatchyFaceX/Faces/analog.h | else | edit ~/Downloads/0-CLOUD/WatchyFaceX/Faces/analog.h | endif
if &buftype ==# 'terminal'
  silent file ~/Downloads/0-CLOUD/WatchyFaceX/Faces/analog.h
endif
balt ~/Downloads/0-CLOUD/WatchyFaceX/Faces/media.h
setlocal foldmethod=indent
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
let s:l = 233 - ((15 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 233
normal! 03|
lcd ~/Downloads/0-CLOUD/WatchyFaceX
wincmd w
exe '1resize ' . ((&lines * 34 + 21) / 42)
exe 'vert 1resize ' . ((&columns * 79 + 79) / 158)
exe '2resize ' . ((&lines * 34 + 21) / 42)
exe 'vert 2resize ' . ((&columns * 89 + 79) / 158)
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
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
