# FibPseudoprime

go install the following extensions on VSC:
1) C/C++ (comes with intellisense https://docs.microsoft.com/en-us/visualstudio/ide/visual-cpp-intellisense?view=vs-2019)
2) Clang-Format (formats c++ code on save)

press command+shift+P, and navigate to preferences: open settings (JSON)
make sure " "editor.formatOnSave": true, " exists in the json file
make sure the following bit of code exists in the json file as well:

```
"[cpp]": {
    "editor.defaultFormatter": "xaver.clang-format"
}
```
