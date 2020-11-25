def test_ad():
    from .adventurer import Adventurer
    def test_function(x):
        x = x+1
        x = 2+x
        x += 10
        return -x
    peek = Adventurer(name=test_function.__name__)
    peek = test_function(peek)
    print(peek)
    
    
    
if __name__ == "__main__":
    test_ad()