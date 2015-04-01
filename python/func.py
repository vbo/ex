def openRange(start):
    while True:
        yield start
        start += 1


def take(n, it):
    while n > 0:
        yield next(it)
        n -= 1


def takeWhile(pred, it):
    for x in it:
        if not pred(x):
            return
        yield x


def any(it):
    for x in it:
        if x:
            return True
    return False


def primes_rec():
    def sieve(it):
        p = next(it)
        yield p
        yield from sieve(x for x in it if x % p > 0)

    yield from sieve(openRange(2))


def primes_iter():
    gen = lambda it, p: (x for x in it if x % p > 0)
    it = openRange(2)
    while True:
        p = next(it)
        yield p
        it = gen(it, p)


def foldl(f, z, xs):
    try:
        x = next(xs)
    except StopIteration:
        return z
    return foldl(f, f(z, x), xs)


def foldlIterative(f, z, xs):
    for x in xs:
        z = f(z, x)
    return z


def foldr(f, z, xs):
    try:
        x = next(xs)
    except StopIteration:
        return z
    return f(x, foldr(f, z, xs))


def lazy_foldr(f, z, xs):
    try:
        x = next(xs)
    except StopIteration:
        return z
    return f(x, lambda: lazy_foldr(f, z, xs))


if __name__ == "__main__":
    print(list(take(5, openRange(0))))
    print(list(takeWhile(lambda x: x < 10, openRange(0))))
    print(any(map(lambda x: x > 10, openRange(0))))
    print(any(map(lambda x: x > 10, take(9, openRange(0)))))
    print(list(take(50, primes_rec())))
    print(list(take(500, primes_iter())))
    print(foldl(lambda z, x: z + x, 0, take(5, openRange(0))))
    print(foldlIterative(lambda z, x: z + x, 0, take(5, openRange(0))))
    print(foldr(lambda z, x: z + x, 0, take(5, openRange(0))))

    def cons(x, z):
        yield x
        yield from z

    def emp():
        return
        yield

    # print(list(take(0, foldr(cons, emp(), openRange(0))))) # this does not work because of strictness =(

    def cons_for_lazy(x, z):
        yield x
        yield from z()

    print(list(take(10, lazy_foldr(cons_for_lazy, emp, openRange(0)))))  # this works because of manual lazyfication ;)
