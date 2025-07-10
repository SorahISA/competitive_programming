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
    val S = readStrings()

    val sizeToInt = { str: String ->
        if (str == "M") 0
        else str.length * (if (str.last() == 'S') -1 else 1)
    }

    if (S[0] == S[1]) println("=")
    else println(if (sizeToInt(S[0]) < sizeToInt(S[1])) "<" else ">")
}

fun main() {
    var t = readInt()

    for (i in 1..t) {
        solve()
    }
}
