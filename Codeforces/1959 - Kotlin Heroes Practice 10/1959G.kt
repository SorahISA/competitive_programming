import kotlin.math.*

private fun readLn() = readLine()!!
private fun readString() = readLn()
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readDouble() = readLn().toDouble()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
private fun readLongs() = readStrings().map { it.toLong() }
private fun readDoubles() = readStrings().map { it.toDouble() }

data class MutablePair<T, U>(var first: T, var second: U)

fun solve() {
    val (N, H) = readInts()
    
    val A = readLongs().sorted()
    // println(A)
    
    val dp = Array(N + 1) { Array(3) { Array(2) { H.toLong() } } }
    for (i in 0..N) {
        for (g in listOf(2, 1, 0)) {
            for (b in listOf(1, 0)) {
                if (i < N) dp[i + 1][g][b] = maxOf(dp[i + 1][g][b], dp[i][g][b] + if (dp[i][g][b] > A[i]) A[i] / 2 else 0)
                if (g > 0) dp[i][g - 1][b] = maxOf(dp[i][g - 1][b], dp[i][g][b] * 2)
                if (b > 0) dp[i][g][b - 1] = maxOf(dp[i][g][b - 1], dp[i][g][b] * 3)
            }
        }
    }
    
    val canEat = A.count { it < dp[N][0][0] }
    // println(dp[N][0][0])
    println(canEat)
}

fun main() {
    val t = readInt()
    
    repeat(t) {
        solve()
    }
}
