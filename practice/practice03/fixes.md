pre bug fix results:

*TestSumRange1 failed: Expected value= 21. Actual= 15

*TestSumRange2 failed: Expected value= 0. Actual= -5

*TestSumRange3 failed: Expected value= -21. Actual= -20

*TestContainsNegative1 failed: Expected value= false. Actual= vector out of range

*TestContainsNegative2 failed: Expected value= true. Actual= error. vector out of range

*TestContainsNegative3 passed but for wrong reason: Expected value= true. Actual= true.

*TestContainsNegative4 failed: Expected value= false. Actual= vector out of range

*TestFindMax1 failed: Expected value= 1. Actual= vector out of range

*TestFindMax2 passed: Expected value = 0. Actual= 0

*TestFindMax3 failed: Expected value = 33. Actual= vector out of range

bugs:

*line 9: <= instead of <

*line 16: < instead of <=

*line 17: should be < instead of > and should be numbers.at(i)

*line 25: should not return 0. should throw exception

*line 26: not listed as bug but should be numbers.at(i)

*line 27: should be > instead of >= and should be numbers.at(i)

*line 28: i should be 0 and <= should be <

*line 29: not labeled as bug but numbers[i] should be numbers.at(i)

*line 39: not listed but should have std::boolalpha






