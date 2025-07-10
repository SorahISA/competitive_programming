import java.util.PriorityQueue

private fun readLn() = readLine()!!
private fun readString() = readLn()
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readDouble() = readLn().toDouble()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
private fun readLongs() = readStrings().map { it.toLong() }
private fun readDoubles() = readStrings().map { it.toDouble() }

data class Tower(var x: Int = 0, var h: Int = 0)

fun solve() {
    val (N, K) = readInts()
    
    val towers = List(K) { Tower(0, 0) }.toMutableList()
    val Xs = readInts()
    val Hs = readInts()
    for (i in 0..(K - 1)) {
        towers[i] = Tower(Xs[i], Hs[i])
    }
    towers.sortBy { it.x }
    
    val dis = MutableList(N + 1) { N }
    towers.forEach { (x, h) -> dis[x] = minOf(dis[x], -h) }
    
    val pq = PriorityQueue<Pair<Int, Int>>(compareBy<Pair<Int, Int>> { it.first })
    for (i in 1..N) pq.offer(dis[i] to i)
    
    while (pq.isNotEmpty()) {
        val (d, now) = pq.poll()
        if (d != dis[now]) continue
        if (now > 1 && dis[now - 1] > d + 1) {
            dis[now - 1] = d + 1
            pq.offer(dis[now - 1] to now - 1)
        }
        if (now < N && dis[now + 1] > d + 1) {
            dis[now + 1] = d + 1
            pq.offer(dis[now + 1] to now + 1)
        }
    }
    for (i in 1..N) if (dis[i] < 0) dis[i] = 0
    
    val Q = readInt()
    
    val queries = List(Q) { i ->
        val (l, r) = readInts()
        Triple(l, r, i)
    }.toMutableList()
    
    val ans = IntArray(Q)
    
    queries.forEach { (l, r, id) -> ans[id] = dis[l] + dis[r] }
    queries.sortBy { it.first + it.second }
    
    var minCost = N
    var tok = 0
    queries.forEach { (l, r, id) ->
        while (tok < K && towers[tok].x <= (l + r) / 2) {
            minCost = minOf(minCost, -towers[tok].x - towers[tok].h)
            tok++
        }
        ans[id] = minOf(ans[id], maxOf(minCost + r, 0))
    }
    
    queries.reverse()
    minCost = N
    tok = K - 1
    queries.forEach { (l, r, id) ->
        while (tok >= 0 && towers[tok].x >= (l + r + 1) / 2) {
            minCost = minOf(minCost, towers[tok].x - N - towers[tok].h)
            tok--
        }
        ans[id] = minOf(ans[id], maxOf(minCost + N - l, 0))
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
