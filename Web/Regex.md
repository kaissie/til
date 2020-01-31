# Regex

## Characters

|Character|Legend|Example|Sample Match|
|---|---|---|---|
|.|Any character|a.c|a_c|
|\d|one digit from 0 to 9|file_\d\d|file_23|
|\w|one ASCII letter, digit or underscore|\w-\w\w\w|A-b_1|
|\s|space, tab, newline, carriage return|a\sb|a b|
|\D|not \d|file_\D\D|file_ab|
|\W|not \w|\W\W\W\W\W|*-+=)|
|\S|not \s|\S\S\S|a_1|
|\\|Escape special character|\\.\\*\\+\\?\\$\\^\\/\\\\|*+?$^/\|

## Quantifiers

|Quantifier|Legend|Example|Sample Match|
|---|---|---|---|
|?|Once or none|apples?|apple|
|*|Zero or more|A\*B\*C\*|AAACC|
|+|One or more|Version \w-\d+|Version A-123|
|{3}|Exactly three times|\D{3}|XYZ|
|{2,4}|Two to four times|\w{3}|a_1|
|{3,}|Three or more times|\w{3,}|Hello_world|

## Logic

|Logic|Legend|Example|Sample Match|
|---|---|---|---|
|\||OR operand|22\|33|33|
|( ... )|Capturing group| A(nt\|pple)        |Apple|
|\1|Contents of Group 1|(\w)(\d)\1| A1A          |
|\2|Contents of Group 2|(\d)\\+(\d)=\2\+\1| 1+2=2+1      |
|(?: ... )|Non-capturing group|(?:\w)(\d)\1|A11|

## Character Classes

|Character|Legend|Example|Sample Match|
|---|---|---|---|
|[...]|One of the characters in the brackets|T[ao]p|Tap|
|[x-y]|One of the characters in the range from x to y|[A-Z]+|ABSTRACT|
|[^x]|One character that is not x|[^A-w]{3}|xyz|

## Anchors
|Anchor|Legend|Example|Sample Match|
|---|---|---|---|
|^|	Start of string or start of line |^abc.*|abcNews|
|$|	End of string or end of line |.* the Earth$|Center of the Earth|
[regex_quickstart](https://www.rexegg.com/regex-quickstart.html)
