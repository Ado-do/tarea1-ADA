# Build settings
$out_dir = "build";
ensure_path($out_dir);

# Compiler settings
$pdf_mode = 5;                  # 5 = xelatex (1=pdflatex, 4=lualatex)
$latex = 'xelatex -interaction=nonstopmode -synctex=1 %O %S';
$pdflatex = 'xelatex -interaction=nonstopmode -synctex=1 %O %S';
$pdflatex .= ' -shell-escape';  # For minted/pythontex

# Continuous compilation (for VimTeX's -pvc mode)
$preview_continuous_mode = 1;
