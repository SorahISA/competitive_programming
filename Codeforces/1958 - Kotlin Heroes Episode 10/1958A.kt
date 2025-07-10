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
    val N = readInt()
    
    when (N) {
        1, 4, 7 -> println(1)
        2 -> println(2)
        else -> println(0)
    }
}

fun main() {
    val t = readInt()
    
    repeat(t) {
        solve()
    }
}
