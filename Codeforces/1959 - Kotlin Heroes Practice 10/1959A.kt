private fun readLn() = readLine()!!
private fun readString() = readLn()
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readDouble() = readLn().toDouble()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
private fun readLongs() = readStrings().map { it.toLong() }
private fun readDoubles() = readStrings().map { it.toDouble() }

fun solve(N: Int, A: IntArray) {
    val mode = if (A[0] == A[1] || A[0] == A[2]) A[0] else A[1]
    for (i in 0 until N) {
        if (A[i] != mode) {
            println(i + 1)
            return
        }
    }
}

fun main() {
    val t = readInt()

    for (i in 1..t) {
        val N = readInt()
        val A = readInts().toIntArray()
        solve(N, A)
    }
}
