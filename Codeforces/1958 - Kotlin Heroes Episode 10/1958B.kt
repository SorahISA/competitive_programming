private fun readLn() = readLine()!!
private fun readString() = readLn()
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readDouble() = readLn().toDouble()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
private fun readLongs() = readStrings().map { it.toLong() }
private fun readDoubles() = readStrings().map { it.toDouble() }

fun solve() {
    val (K, M) = readInts()
    
    val result = if (M % (3 * K) >= 2 * K) 0 else (2 * K - M % (3 * K))
    println(result)
}

fun main() {
    val t = readInt()
    
    repeat(t) {
        solve()
    }
}
