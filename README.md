# FibPseudoprime

## To Contribute
go install the following extensions on VSC:
1) C/C++ (comes with intellisense https://docs.microsoft.com/en-us/visualstudio/ide/visual-cpp-intellisense?view=vs-2019)
2) Clang-Format (formats c++ code on save)

Press command+shift+P, and navigate to preferences: open settings (JSON)   
Make sure `"editor.formatOnSave": true,` exists in the json file.   
Make sure the following bit of code exists in the json file as well:   

```
"[cpp]": {
    "editor.defaultFormatter": "xaver.clang-format"
}
```
