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
    val N = readInt()
    val A = readInts()
    
    val dp = BooleanArray(N+1) { false }
    dp[0] = true
    for (i in 0 until N+1) {
        if (i >= 1 && i - A[i-1] - 1 >= 0) dp[i] = dp[i] || dp[i - A[i-1] - 1]
        if (i < N && i + A[i] + 1 <= N) dp[i + A[i] + 1] = dp[i + A[i] + 1] || dp[i]
    }
    println(if (dp[N]) "Yes" else "No")
}

fun main() {
    val t = readInt()
    
    repeat(t) {
        solve()
    }
}
