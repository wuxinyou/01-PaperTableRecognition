rem 执行改批处理前先要目录下创建font_properties文件

echo Run Tesseract for Training..
tesseract.exe num.font.exp0.tif num.font.exp0 nobatch box.train

echo Compute the Character Set..
unicharset_extractor.exe num.font.exp0.box
mftraining -F font_properties -U unicharset -O num.unicharset num.font.exp0.tr

echo Clustering..
cntraining.exe num.font.exp0.tr

echo Rename Files..
rename normproto num.normproto
rename inttemp num.inttemp
rename pffmtable num.pffmtable
rename shapetable num.shapetable 

echo Create Tessdata..
combine_tessdata.exe num.
pause