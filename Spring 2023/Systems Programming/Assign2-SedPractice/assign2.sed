/^[ \t]*\/\// { p ; d }
/^[ \t]*#/ { p ; d }
/^[ \t]*\/\*\*/,/^[ \t]*\*\*\// { p ; d }
s/ *\+ */ \+ /g
s/ *- */ - /g
s/ *\* */ \* /g
s/ *\/ */ \/ /g
s/ *= */ = /g
s/ *== */ == /g
s/ *<= */ <= /g
s/ *>= */ >= /g
s/ *< */ < /g
s/ *> */ > /g
s/[ ]{2,}/ /gi #apparently legacy, also just doesnt work in some cases
s/ +$//g
s/\( +/\(/g
s/ +\)/\)/g
