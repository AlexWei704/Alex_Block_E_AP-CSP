def main():
    n = 0;
    while n < 1 or n > 8:
        try:
            n = int(input("Height: "))
        except ValueError:
            continue

    for i in range(1, n+1):
        print(" " * (n - i) + "#" * i + "  " + "#" * i)

if __name__ == "__main__":
    main()
