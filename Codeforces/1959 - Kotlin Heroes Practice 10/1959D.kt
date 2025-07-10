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
    var (_N, _c) = readStrings()
    var N = _N.toInt()
    var c = _c[0]
    var S = readString()
    
    if (c == 'g') { println(0); return }

    var ans = 0
    var cnt = 0
    var pos = S.indexOf('g')
    for (i in 0 until N) {
        if (pos < 0) pos += N
        if (S[pos] == 'g') cnt = 0
        else cnt++
        if (S[pos] == c) ans = max(ans, cnt)
        --pos
    }
    println(ans)
}

fun main() {
    val t = readInt()

    repeat(t) {
        solve()
    }
}
