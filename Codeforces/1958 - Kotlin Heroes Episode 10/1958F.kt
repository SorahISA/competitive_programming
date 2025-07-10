private fun readLn() = readLine()!!
private fun readString() = readLn()
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readDouble() = readLn().toDouble()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
private fun readLongs() = readStrings().map { it.toLong() }
private fun readDoubles() = readStrings().map { it.toDouble() }

const val mod = 1_000_000_007L

fun fpow(_base: Long, _exp: Long = mod - 2): Long {
    var base = _base
    var exp = _exp
    var ans = 1L
    while (exp > 0) {
        if (exp and 1L == 1L) ans = ans * base % mod
        exp = exp shr 1
        base = base * base % mod
    }
    return ans
}

fun solve() {
    val (N, K) = readLongs()
    val Ni = N.toInt()
    val Ki = K.toInt()
    
    val fact = LongArray(2 * Ni + 1) { 1L }
    val ifac = LongArray(2 * Ni + 1) { 1L }
    for (i in 1..(2 * Ni)) {
        fact[i] = fact[i - 1] * i.toLong() % mod
    }
    ifac[2 * Ni] = fpow(fact[2 * Ni])
    for (i in (2 * Ni) downTo 1) {
        ifac[i - 1] = ifac[i] * i.toLong() % mod
    }
    
    fun C(n: Int, m: Int): Long {
        if (n < m || m < 0) return 0L
        return fact[n] * ifac[m] % mod * ifac[n - m] % mod
    }
    
    val ans = LongArray(Ni + 1) { 0L }
    ans[0] = C(2 * Ni - 2, Ki)
    for (i in 1..(Ni - 1)) {
        ans[i] = (C(Ni - i - 2, Ki - 2) * (N - i - 1) + C(Ni - i - 1, Ki - 1) * 2) % mod
        ans[0] = (ans[0] - ans[i] + mod) % mod
    }
    
    println(ans.joinToString(" "))
}

fun main() {
    // val t = readInt()
    val t = 1
    
    repeat(t) {
        solve()
    }
}
