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
    val (N, K) = readInts()
    
    val minNeed = listOf(1, 2, 3, 5, 9, 17, 33, 65)
    
    if (K > 7 || N < minNeed[K]) {
        println(-1)
        return
    }
    
    var ans = mutableListOf(N, N - 1)
    var tok = N - 2
    for (round in 2..K) {
        val tmp = mutableListOf<Int>()
        for (i in ans.indices) {
            if (i != 0) tmp.add(tok--)
            tmp.add(ans[i])
        }
        ans = tmp
    }
    while (tok >= 1) ans.add(tok--)
    
    println(ans.joinToString(" "))
}

fun main() {
    val t = readInt()
    
    repeat(t) {
        solve()
    }
}
