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
    val A = readLongs()
    
    var ans = 0L
    var i = 0
    while (i < N) {
        if (A[i] == 0L) {
            i++
            continue
        }
        var sum = 0L
        var len = 0L
        var oddMax = A[i]
        while (i < N && A[i] != 0L) {
            sum += A[i]
            if (++len % 2 == 1L) oddMax = maxOf(oddMax, A[i])
            i++
        }
        ans += 2 * sum - (if (len % 2 == 1L) oddMax else 0)
    }
    println(ans)
}

fun main() {
    val t = readInt()
    
    repeat(t) {
        solve()
    }
}
