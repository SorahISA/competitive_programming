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
    var (N, K) = readInts()
    var S = readString()

    var cnt = Array(26) { MutablePair(0, 0) }
    for (c in S) {
        if (c.isLowerCase()) ++cnt[c - 'a'].first
        else ++cnt[c - 'A'].second
    }

    var ans = 0
    for ((lo, up) in cnt) {
        ans += minOf(lo, up) + minOf(abs(lo - up) / 2, K)
        K -= minOf(abs(lo - up) / 2, K)
    }
    println(ans)
}

fun main() {
    var t = readInt()

    repeat(t) {
        solve()
    }
}
