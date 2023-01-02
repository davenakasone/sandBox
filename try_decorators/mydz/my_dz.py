import functools
import time

def my_timer(fun) :
    "print runtime of decorated function"
    @functools.wraps(fun)
    def t_wrapper(*args, **kwargs) :
        start_t = time.perf_counter()
        r_val = fun(*args, **kwargs)
        end_t = time.perf_counter()
        run_t = end_t - start_t
        print(f"{fun.__name__}()  time:{run_t:0.4f} seconds") # or {fun.__name__!r} == repr()
        return r_val
    return t_wrapper

def my_debug(fun):
    """print a signature + return value for logging calls"""
    @functools.wraps(fun)
    def d_wrapper(*args, **kwargs) :
        rep_args = [repr(a) for a in args]
        rep_kwargs = [f"{k}={v!r}" for k, v in kwargs.items()]
        sig = ", ".join(rep_args + rep_kwargs)
        print(f"{fun.__name__}({sig})")
        rv = fun(*args, **kwargs)
        print(f"-->  {rv}\n")
        return rv
    return d_wrapper

def my_twice(fun) :
    def wrap_2(*args, **kwargs):
        fun(*args, **kwargs)
        return fun(*args, **kwargs)
    return wrap_2

def my_repeat(_func=None, repz=2) :
    def decorator_repeat(fun) :
        @functools.wraps(fun)
        def wrapper_r(*args, **kwargs) :
            for _ in range(repz) :
                rv = fun(*args, **kwargs)
            return rv
        return wrapper_r
    if _func is None :
        return decorator_repeat
    else :
        return decorator_repeat(_func)

def my_ccount(func) :
    @functools.wraps(func)
    def wrapper_cc(*args, **kwargs) :
        wrapper_cc.calls += 1
        print(f"{func.__name__}()  ,  calls:  {wrapper_cc.calls}")
        return func(*args, **kwargs)
    wrapper_cc.calls = 0 # set an attribute of the object 'wrapper_cc()'
    return wrapper_cc

def my_slow(_func=None, *, rate:int=1) :
    def decorate_slow(func):
        @functools.wraps(func)
        def wrap_slow(*args, **kwargs):
            time.sleep(rate)
            return func(*args, **kwargs)
        return wrap_slow
    if _func is None :
        return decorate_slow
    else :
        return decorate_slow(_func)

def my_single(cls):
    def wrap_s(*args, **kwargs) :
        if not wrap_s.instance :
            wrap_s.instance = cls(*args, **kwargs)
        return wrap_s.instance
    wrap_s.instance = None
    return wrap_s

def my_fcache(func):
    @functools.wraps(func)
    def wrapc(*args, **kwargs):
        ckey = args + tuple(kwargs.items())
        if ckey not in wrapc.cache:
            wrapc.cache[ckey]=func(*args, **kwargs)
        return wrapc.cache[ckey]
    wrapc.cache = dict()
    return wrapc

class Ccounter:
    def __init__(self, start=0):
        self.count = start
    def __call__(self):
        self.count += 1
        print(f"calls: {self.count}")

class CcounterC:
    def __init__(self, fun) :
        functools.update_wrapper(self, fun)
        self.func = fun
        self.count = 0  
    def __call__(self, *args, **kwargs):
        self.count += 1
        print(f"calls: {self.count}")
        return self.func(*args, **kwargs)

