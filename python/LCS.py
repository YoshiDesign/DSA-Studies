def longest_common_subsequence(X, Y):

    m, n = len(X), len(Y)
    # Zero-Fill a 2D array
    dp = [[0] * (n + 1) for _ in range(m + 1)]

    for i in range(m):
        for n in range(n):
            

if __name__ == "__main__":
    longest_common_subsequence("abc", "abcdefghijkl")