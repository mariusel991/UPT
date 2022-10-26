# EX 1

def prog_aritmetica(n):
    if (n == 0):
        return 2
    else:
        return 2 * prog_aritmetica(n - 1) - 3


print(prog_aritmetica(3))
print("EX1 ------------------------------------------------------------")


# ---------------------------------------------


# EX 2

def fibonacci(n):
    if (n == 1):
        return 1

    elif (n == 0):

        return 0
    else:
        return fibonacci(n - 1) + fibonacci(n - 2)


print(fibonacci(7))
print("EX2 ------------------------------------------------------------")


# ------------------------------------------------

# EX 3

def suma(n):
    return int(((n * (n + 1)) / 2))


def suma(n):
    if (n == 1):
        return 1
    else:
        return n + suma(n - 1)


print(suma(3))
print("EX3 ------------------------------------------------------------")


# EX 4

#
def cif_nr(x):
    if (x <= 9):
        return x

    else:
        return x % 10 + cif_nr(x / 10)


print(int(cif_nr(333)))


# a)

def cif_nr_a(x):
    if (x <= 9):
        return x

    else:
        return x % 10 * cif_nr_a(x // 10)


print(cif_nr_a(123))


# b)

def cifre_b(n):
    if (n < 10):
        return 1
    else:
        return 1 + cifre_b(n // 10)


print(cifre_b(213))


# ------------------------------------------------------------

# c)

def cifre_c(n):
    def aux(nr, m=0):
        if (nr < 10):
            return max(nr, m)
        else:
            return aux(nr // 10, m=max(nr % 10, m))

    return aux(n)


print(cifre_c(987))
print(cifre_c(123))


# ----------------------------------------------

# d)

def cifre_d(n):
    if (n < 10):
        if (n % 2 == 0):
            return 1
        else:
            return 0

    else:
        if (n % 2 == 0):
            return 1 + cifre_d(n // 10)
        else:
            return 0 + cifre_d(n // 10)


print(cifre_d(987))
print(cifre_d(222))
print("EX4 ------------------------------------------------------------")


# EX 5

def exponent(n, p, val=1):
    if (p == 0):
        return 1

    elif (p == 1):
        return val * n

    else:
        return exponent(n, p - 1, val=val * n)


print(exponent(2, 4))
print("EX5 ------------------------------------------------------------")


# ---------------------------------------------------

# EX 6

def prim(m):
    def prim_aux(n, i):
        if (i > n / 2):
            return True

        else:
            if (n % i == 0):
                return False
            else:
                return True and prim_aux(n, i + 1)

    return prim_aux(m, 2)


print("EX6 ------------------------------------------------------------")


# -----------------------------------------------------------------------------

# EX 7

def cmmdc(a, b):
    if (b == 0):
        return a
    else:
        return cmmdc(b, a % b)


print(cmmdc(16, 32))
print("EX7 ------------------------------------------------------------")


# ------------------------------------------------------------------------------

# EX 8

def print_my_reverse(s):
    if (len(s) == 0):
        return s
    else:
        return print_my_reverse(s[1:]) + s[0]


print(print_my_reverse("rava"))

print("EX8 ------------------------------------------------------------")

# ---------------------------------------------------------------------------------

# EX 9


def interval(min_value, max_value):
    def step(i=min_value, M=max_value):
        if (i == M):
            print(M)
            return None
        else:
            print(i)
            return step(i + 1, M)

    return step(min_value, max_value)


print(interval(5, 10))

print("EX9 ------------------------------------------------------------")


# ---------------------------------------------------------------------------------

# EX 10 A)
def aparitii_a(n, c):
    if (n < 10):
        if (n % 10 == c):
            return True
        else:
            return False

    else:
        if (n % 10 == c):
            return True or aparitii_a(n // 10, c)
        else:
            return False or aparitii_a(n // 10, c)


print(aparitii_a(231, 9))
print(aparitii_a(213, 3))


# B)
def aparitii_b(n, c):
    if (n < 10):
        if (n % 10 == c):
            return 1
        else:
            return 0

    else:
        if (n % 10 == c):
            return 1 + aparitii_b(n // 10, c)
        else:
            return 0 or aparitii_b(n // 10, c)


print(aparitii_b(231, 9))
print(aparitii_b(333, 3))

print("EX10 ------------------------------------------------------------")


# --------------------------------------------------------------------------

# EX 11

def palindrom(n):
    def aux(n1, sol=0):
        if (n1 < 10):
            return sol * 10 + n1 % 10
        else:
            return aux(n1 // 10, sol=sol * 10 + n1 % 10)

    if (aux(n) == n):
        return True
    else:
        return False


print(palindrom(505))
print(palindrom(521))
print("EX11 ------------------------------------------------------------")


# ------------------------------------------------------------------------------------------------------

# EX 12

def f(x):
    return x + 1


def comp(f, x, n):
    if (n == 0):
        return x
    else:
        return f(comp(f, x, n - 1))


print(comp(f, 5, 2))
print("EX12 ------------------------------------------------------------")


# ------------------------------------------------------------------------------------------------------------------

# EX 13

# A)
def suma_a(n):
    if (n == 1):
        return 1
    else:
        return 1 / n + suma_a(n - 1)


print(suma_a(10))
print("------------a)")

# B
# --- NOT DONE YET!

# C

import math as m


def suma_c(n):
    if (n == 1):
        return 1
    else:
        return m.sqrt(1 + m.sqrt(suma_c(n - 1)))


print(suma_c(3))
print("-------------c)")

print("EX13 ------------------------------------------------------------")


# EX 1

def prog_aritmetica(n):
    if (n == 0):
        return 2
    else:
        return 2 * prog_aritmetica(n - 1) - 3


print(prog_aritmetica(3))
print("EX1 ------------------------------------------------------------")


# ---------------------------------------------


# EX 2

def fibonacci(n):
    if (n == 1):
        return 1

    elif (n == 0):

        return 0
    else:
        return fibonacci(n - 1) + fibonacci(n - 2)


print(fibonacci(7))
print("EX2 ------------------------------------------------------------")


# ------------------------------------------------

# EX 3

def suma(n):
    return int(((n * (n + 1)) / 2))


def suma(n):
    if (n == 1):
        return 1
    else:
        return n + suma(n - 1)


print(suma(3))
print("EX3 ------------------------------------------------------------")


# EX 4

#
def cif_nr(x):
    if (x <= 9):
        return x

    else:
        return x % 10 + cif_nr(x / 10)


print(int(cif_nr(333)))


# a)

def cif_nr_a(x):
    if (x <= 9):
        return x

    else:
        return x % 10 * cif_nr_a(x // 10)


print(cif_nr_a(123))


# b)

def cifre_b(n):
    if (n < 10):
        return 1
    else:
        return 1 + cifre_b(n // 10)


print(cifre_b(213))


# ------------------------------------------------------------

# c)

def cifre_c(n):
    def aux(nr, m=0):
        if (nr < 10):
            return max(nr, m)
        else:
            return aux(nr // 10, m=max(nr % 10, m))

    return aux(n)


print(cifre_c(987))
print(cifre_c(123))


# ----------------------------------------------

# d)

def cifre_d(n):
    if (n < 10):
        if (n % 2 == 0):
            return 1
        else:
            return 0

    else:
        if (n % 2 == 0):
            return 1 + cifre_d(n // 10)
        else:
            return 0 + cifre_d(n // 10)


print(cifre_d(987))
print(cifre_d(222))
print("EX4 ------------------------------------------------------------")


# EX 5

def exponent(n, p, val=1):
    if (p == 0):
        return 1

    elif (p == 1):
        return val * n

    else:
        return exponent(n, p - 1, val=val * n)


print(exponent(2, 4))
print("EX5 ------------------------------------------------------------")


# ---------------------------------------------------

# EX 6

def prim(m):
    def prim_aux(n, i):
        if (i > n / 2):
            return True

        else:
            if (n % i == 0):
                return False
            else:
                return True and prim_aux(n, i + 1)

    return prim_aux(m, 2)
print(prim(33))

print("EX6 ------------------------------------------------------------")


# -----------------------------------------------------------------------------

# EX 7

def cmmdc(a, b):
    if (b == 0):
        return a
    else:
        return cmmdc(b, a % b)


print(cmmdc(16, 32))
print("EX7 ------------------------------------------------------------")


# ------------------------------------------------------------------------------

# EX 8

def print_my_reverse(s):
    if (len(s) == 0):
        return s
    else:
        return print_my_reverse(s[1:]) + s[0]


print(print_my_reverse("rava"))

print("EX8 ------------------------------------------------------------")

# ---------------------------------------------------------------------------------

# EX 9


def interval(min_value, max_value):
    def step(i=min_value, M=max_value):
        if (i == M):
            print(M)
            return None
        else:
            print(i)
            return step(i + 1, M)

    return step(min_value, max_value)


print(interval(5, 10))

print("EX9 ------------------------------------------------------------")


# ---------------------------------------------------------------------------------

# EX 10 A)
def aparitii_a(n, c):
    if (n < 10):
        if (n % 10 == c):
            return True
        else:
            return False

    else:
        if (n % 10 == c):
            return True or aparitii_a(n // 10, c)
        else:
            return False or aparitii_a(n // 10, c)


print(aparitii_a(231, 9))
print(aparitii_a(213, 3))


# B)
def aparitii_b(n, c):
    if (n < 10):
        if (n % 10 == c):
            return 1
        else:
            return 0

    else:
        if (n % 10 == c):
            return 1 + aparitii_b(n // 10, c)
        else:
            return 0 or aparitii_b(n // 10, c)


print(aparitii_b(231, 9))
print(aparitii_b(333, 3))

print("EX10 ------------------------------------------------------------")


# --------------------------------------------------------------------------

# EX 11

def palindrom(n):
    def aux(n1, sol=0):
        if (n1 < 10):
            return sol * 10 + n1 % 10
        else:
            return aux(n1 // 10, sol=sol * 10 + n1 % 10)

    if (aux(n) == n):
        return True
    else:
        return False


print(palindrom(505))
print(palindrom(521))
print("EX11 ------------------------------------------------------------")


# ------------------------------------------------------------------------------------------------------

# EX 12

def f(x):
    return x + 1


def comp(f, x, n):
    if (n == 0):
        return x
    else:
        return f(comp(f, x, n - 1))


print(comp(f, 5, 2))
print("EX12 ------------------------------------------------------------")


# ------------------------------------------------------------------------------------------------------------------

# EX 13

# A)
def suma_a(n):
    if (n == 1):
        return 1
    else:
        return 1 / n + suma_a(n - 1)


print(suma_a(10))
print("------------a)")

# B
# --- NOT DONE YET!

# C

import math as m


def suma_c(n):
    if (n == 1):
        return 1
    else:
        return m.sqrt(1 + m.sqrt(suma_c(n - 1)))


print(suma_c(3))
print("-------------c)")

print("EX13 ------------------------------------------------------------")
