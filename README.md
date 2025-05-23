------------

How to use test files
---------------------
./spchk ../dict ./TextTestCases/Correct //Demonstrates all the correct test cases, and should return no error
./spchk ../dict ./TextTestCases/Incorrect //Demonstrate all the incorrect test cases, and should return error on every line.
./spchk ../dict ./DirectoryTestCases //Demonstrates the traversal and skipping of files and directories with "." .

Test Plan
---------
For the test plan, the dictionary was created via the ilab's dictionary removing all non-ascii characters with the find all and regex function.
The dictionary has a few words added to make sure that the test file passes all the spellchecks, located at the end of the dict file
This provided a massive dictionary of words that were able to be used and tested.
For test case, there were two seperate divisions:
1.) Text files, having to do with punctuation, hyphens, and capitlization, and the spellcheck function's intereactions with the text files themselves
2.) Directory and traversal, having to do with the proper function of reading through directory files, and ensuring that directories and files starting with '.' were ignored, alongn with being able to fully traverse a directory.

With the test cases broken down, the text file were created into two categories, correct and incorrect. 

"Correct Capitlization.txt"
--------------------------
there were 3 acceptable varation of words without capitlization in the middle and 2 acceptable variation of words with capitlization in the middle
For the word "hello", acceptable variables include "hello", "Hello", and "HELLO".
For the word "MacDonald", acceptable variables include "MacDonald" and "MACDONALD".
Those are the only acceptable variations, and are the ones tested for correctness in "Correct Capitlization".

"Incorrect Capitlization.txt"
-----------------------------
For incorrect variations, it was just handle the 4 to 5 possible variations of the word, and making sure the non-acceptable ones weren't acceptable.
For the word "hello", the only unacceptable variation is "hEllO" or any similar varation where capitlization is not uniform.
For the word "MacDonald", there are a bit more variation. The unacceptable varations include "MacDonald", "macdonald", and "mACDoNALD". 

"Correct Hyphens.txt"
---------------------
For hyphens, the logic behind correct testings where just to include basic words, with variations in capitlization (electric-Car vs Electric-car vs Electric-Car), in which case, all would be correct.
Accepting multi-hyphened words was next, including sentenes constructed via hyphens. 
Lastly, there were more complex hyphened words, including random punctuation, and apostrophes.

"Incorrect Hyphens.txt"
-----------------------
Most of the incorrect hyphens include variation of the first word being incorrect, the second word being incorrect, both being incorrect, and more complex variations if it's a multi-hyphenated word. 
Variations of incorrectness were included, using incorrect capitlization and just general misspelling.

"Correct Punctuation.txt"
-------------------------
Correct punctuation just included all variations of parenthesis, quotations, and contractions. Variations include:
"{word}", "[word]", "(word)", word?, "word!", "word.", ""word"", and "'word'" with the contraction being "haven't"
There was a problem with "'" because it couldn't just be replaced using strtok, so a roundabout way of stripping words beginning and ending with "'" was needed, so a varaition that included multiple "'" was included.

"incorrect Puncutation.txt"
---------------------------
For incorrect punctuation, the same variations as listed before were used, but using a mispelled word to ensure that the incorrect word would be printed. Also a contraction lacking a "'" was included.

"Correct Complex.txt"
---------------------
This includes a small conversation between two individuals containing various symbols, hyphens, contractions, and quotes to make sure everything functions togethor.

"testfile.txt"
-----------------
This is the script of Kung Fu Panda, and I included various words into the dictionary to ensure everything functions properly. The added words are included at the tail-end of the dictionary. 

DirectoryTestCases
------------------
For DirectoryTestCases, the cases were a bit more nuanced. 
The first test was ensuring that files and directories beginning with "." were excluded, so there is a directory named ".DoNotEnter" with a file inside called "thisisasecret.txt" with an incorrect word.
If the incorrect word is reported, the directory was traversed through and the code would need to be edited.
The second test case was "Directory1" containing a file ".IgnoreThis.txt" which should be ignored sicne it has a "." at the start, but also contains ".txt" If the incorrect word is reported, then the code traversed into the file, meaning there's an error
The third test case was the file named "ignoreThis" inside "Directory1". The file doesn't end with txt, so it should be unreadable.
The last test case was in "Directory0" and is named "Readable0.txt" which should be read, and contains an error that should be reported.

Design Notes
------------
One of the strange things was counting row and column numbers. It was very abstract, so I went with a line and column counter that VSCode has, and made sure everything matched unacceptable
Anther strange thing is that there's another type of hyphen I encountered while testing my code, "—", which is more of a double hyphen. I originally planned to cover this case, but the write up said "-" only so I decided to ignore this.
There's also a strange case of numbers, I decided that it was more ideal to just ignore numbers in general. 
