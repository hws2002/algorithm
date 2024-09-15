t = int(input())

discovered = []
finished = []
adj = [[]]

def dag(start : int, adj : list) :
    vcnt = 0
    res = []
    impossible = False
  # for l in adj:
  #   for e in l:
  #     print(e, end = ' ')
  #   print('')

  def dfs(here):
    nonlocal vcnt
    nonlocal impossible
    global discovered
    global finished
  

    discovered[here] = vcnt
    vcnt += 1
    
    for next_t, cango in enumerate(adj[here]):
      if not cango :
        continue
      if discovered[next_t] == -1 : # 트리 간선
        dfs(next_t)
      if discovered[next_t] != -1 :
        if discovered[next_t] > discovered[here] : # 순방향 간선
          continue
        
        if not finished[next_t] :  # 사이클 발견
          impossible = True
          return
        else : # 교차 간선
          continue
        
      if impossible:
        return
    finished[here] = True
    res.append(here+1)
    return
  
  dfs(start)
  if impossible : 
    print("IMPOSSIBLE")
  else :
    print(*res[::-1])
  return


def solve():
  global finished
  global discovered
  n = int(input())
  finished = [False] * n
  discovered = [-1] * n
  rank2team = list(map(lambda x : int(x)-1, input().split()))
  adj = [ [0] * n for _ in range(n)]
  
  indegree = [0] * n
  for i, team in enumerate(rank2team):
    for j in range(i+1,n):
      adj[team][rank2team[j]] = 1
    indegree[team] = i

  m = int(input())
  for _ in range(m):
    a, b = map(lambda x : int(x) - 1, input().split())
    if adj[b][a]: # b의 랭크가 a보다 높음
      a, b = b, a
      
    if adj[a][b] == 1:
      indegree[b] -= 1
    adj[a][b] = 0
    
    if adj[b][a] == 0:
      indegree[a] += 1
    adj[b][a] = 1 
  
  #print(indegree)
  v_indegree_0 = [v for v,d in enumerate(indegree) if d == 0]
  
  if len(v_indegree_0) > 2:
    print('?')
    return
  elif len(v_indegree_0) != 1:
    print('IMPOSSIBLE')
    return
  
  # run DAG
  dag(v_indegree_0[0], adj)
  
while t:
  solve()
  t -= 1