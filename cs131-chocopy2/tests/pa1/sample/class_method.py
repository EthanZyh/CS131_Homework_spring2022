class Foo(object):
    x:int = 0
    def set(self:"Foo", x:int) -> object:
        self.x = x
ff = Foo()
ff.set(1)
print(f.x)
