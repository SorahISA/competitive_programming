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
    val S = readString()
    val N = S.length

    val pos = Array(26) { mutableListOf<Int>() }
    for (i in 0 until N) {
        pos[S[i] - 'a'].add(i + 1)
    }

    val ans = mutableListOf<Int>()
    val cost = abs(S[0].toInt() - S[N - 1].toInt())
    val dir = if (S[0] <= S[N - 1]) 1 else -1
    var c = S[0] - 'a';
    while (c != (S[N - 1] - 'a') + dir) {
        ans.addAll(pos[c])
        c += dir
    }

    println("$cost ${ans.size}")
    println(ans.joinToString(" "))
}

fun main() {
    val t = readInt()

    repeat(t) {
        solve()
    }
}
