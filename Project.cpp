/*
                 ****Project description****
           *Driver can go either maximum or minimum path(using spanning tree)
           *If a node does not have any connected city rather than his parent then the driver will 
            return to previous city and the distance will be double.
           *Driver will earn 50 taka for per km.
           *Car can run 12 km per liter
           *Profit = Income - oil cost
           *Knapsack
           ***Submitted by:
                           *Md. Nahid Hasan
                           ID: 2019-1-60-207
                           *Marwa Khanom Nurtaj
                           ID:2019-1-60-255
                           *Rafsan Bari Shafin
                           ID:2019-1-62-001
*/
#include <bits/stdc++.h>
using namespace std;

struct edge
{
    int u, v, w;
} edges[200005], col[200000];

struct Item
{
    int budget;
    int weight;
};

int knapsackItemNumber, limitBudget;
Item b[1005];
int dp[1005][1005];
int choice[1005][1005];
int par[100005], size[100005];

bool cmp(edge a, edge b) // condition for minimum spanning tree
{
    return a.w < b.w;
}
bool cmp1(edge a, edge b) //condition for maximum spanning tree
{
    return a.w > b.w;
}

void init(int n)
{
    for (int i = 1; i <= n; i++)
    {
        par[i] = -1;
        size[i] = 1;
    }
}

int findRoot(int u)
{
    if (par[u] == -1)
        return u;
    return findRoot(par[u]);
}

int merger(int u, int v)
{
    u = findRoot(u);
    v = findRoot(v);
    if (u == v)
        return 0;
    if (size[u] < size[v])
        swap(u, v);
    par[v] = u;
    size[u] = size[v] + size[u];
    return 1;
}

int minimumSpanningTree(int n, int e) // function for minimum spanning tree
{
    int sum = 0;
    init(n);
    sort(edges, edges + e, cmp);
    printf("\n");
    for (int i = 0; i < e; i++)
    {
        if (merger(edges[i].u, edges[i].v) == 1)
        {
            sum += edges[i].w;
            col[i].u = edges[i].u;
            col[i].v = edges[i].v;
            col[i].w = edges[i].w;
        }
    }
    int sum2 = 0;
    for (int i = 0; i < e; i++)
    {
        int sum1 = 0;
        for (int j = 0; j < e; j++)
        {
            if (col[i].v != col[j].u)
            {
                sum1++;
            }
        }
        if (sum1 == e)
        {
            sum2 += col[i].w;
        }
    }

    int sum3 = sum2 + sum; // after both added
                           //cout<<sum2<<endl;  // extra distance covered
                           //cout<<sum<<endl;  // normal distance covered
    return sum3;
}

int maximumSpanningTree(int n, int e) //function for maximum spanning tree
{
    int sum = 0;
    init(n);
    sort(edges, edges + e, cmp1);
    printf("\n");
    for (int i = 0; i < e; i++)
    {
        if (merger(edges[i].u, edges[i].v) == 1)
        {
            sum += edges[i].w;
            col[i].u = edges[i].u;
            col[i].v = edges[i].v;
            col[i].w = edges[i].w;
        }
    }
    int sum2 = 0;
    for (int i = 0; i < e; i++)
    {
        int sum1 = 0;
        for (int j = 0; j < e; j++)
        {
            if (col[i].v != col[j].u)
            {
                sum1++;
            }
        }

        if (sum1 == e)
        {
            sum2 += col[i].w;
        }
    }

    int sum3 = sum2 + sum; // after both added
                           //cout<<sum2<<endl;  // extra distance covered
                           //cout<<sum<<endl;  // normal distance covered
    return sum3;
}

int knapsack(int c, int rem)
{
    if (c == knapsackItemNumber)
        return 0;
    if (dp[c][rem] != -1)
        return dp[c][rem];
    int op1 = knapsack(c + 1, rem);
    int op2 = 0;
    if (b[c].budget <= rem)
    {
        op2 = b[c].weight + knapsack(c + 1, rem - b[c].budget);
    }
    if (op1 >= op2)
    {
        choice[c][rem] = 0;
        return dp[c][rem] = op1;
    }
    choice[c][rem] = 1;
    return dp[c][rem] = op2;
}

int main()
{
    cout << "*************************************A DAY LIFE OF UBER DRIVER ***************************************" << endl
         << endl
         << endl;
    int u, v, w;
    int n, e, price;
    cout << " Enter the number of City and Corresponding road number " << endl;
    cin >> n >> e;
    cout << " Enter the citys which have roads between them with the distance " << endl;
    for (int i = 0; i < e; i++)
    {
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }
    while (1)
    {
        cout << " Press 1. to Cover Minimum Distance" << endl;
        cout << " Press 2. to Cover Maximum Distance" << endl;
        cout << " Press 3. Exit" << endl;

        cout << " Choose an option :" <<endl;
        int option, s;
        cin >> option;
        switch (option)
        {
        case 1:
        {
            for (int i = 0; i < e; i++)
            {
                col[i].u = -1;
                col[i].v = -1;
                col[i].w = -1;
            }
            int p = minimumSpanningTree(n, e);
            int pt = p * 50; //
            cout << " The minimum cover distance :" << p << "Km" << endl;
            cout << " Total income :" << pt << "Taka" << endl;
            float pet = p / 12; // we guess that by 1 litre petrol we can travel 12 km
            cout << " Enter the petrol current price :";
            cin >> price;
            cout << endl;
            float j = pet * price;
            cout << " The petrol will cost :" << j << endl;
            cout << " Atfer removing petrol price the amount remaining will be " << endl;
            s = pt - j;
            cout << s << endl;

            limitBudget = s;
            printf(" Number of items?\n");
            scanf("%d", &knapsackItemNumber);

            for (int i = 0; i < knapsackItemNumber; i++)
            {
                printf(" No. %d Item's weight and corresponding price: ", i + 1);
                scanf("%d%d", &b[i].weight, &b[i].budget);
            }

            for (int i = 0; i <= knapsackItemNumber; i++)
            {
                for (int j = 0; j <= limitBudget; j++)
                    dp[i][j] = -1;
            }
            printf("\n Maximum number of weight can be gathered:");
            printf("%d\n", knapsack(0, limitBudget));
            printf("\n Iteam numbered:");

            int getIteam = 0;
            int rem = limitBudget;

            while (getIteam != knapsackItemNumber)
            {
                if (choice[getIteam][rem] == 0)
                {
                    getIteam++;
                }
                else
                {
                    printf("%d, ", getIteam + 1);
                    rem -= b[getIteam].budget;
                    getIteam++;
                }
            }
            printf("should be taken\n");
            break;
        }
        case 2:
        {
            for (int i = 0; i < e; i++)
            {
                col[i].u = -1;
                col[i].v = -1;
                col[i].w = -1;
            }
            int p = maximumSpanningTree(n, e);
            int pt = p * 50; //
            cout << " The minimum cover distance :" << p << "Km" << endl;
            cout << " Total income :" << pt << "Taka" << endl;
            float pet = p / 12; // we guess that by 1 litre petrol we can travel 12 km
            cout << " Enter the petrol current price :";
            cin >> price;
            cout << endl;
            float j = pet * price;
            cout << " The petrol will cost :" << j << endl;
            cout << " Atfer removing petrol price the amount remaining will be " << endl;
            s = pt - j;
            cout << s << endl;

            limitBudget = s;
            printf(" Number of items?\n");
            scanf("%d", &knapsackItemNumber);

            for (int i = 0; i < knapsackItemNumber; i++)
            {
                printf(" No. %d Item's weight and corresponding price: ", i + 1);
                scanf("%d%d", &b[i].weight, &b[i].budget);
            }

            for (int i = 0; i <= knapsackItemNumber; i++)
            {
                for (int j = 0; j <= limitBudget; j++)
                    dp[i][j] = -1;
            }
            printf("\n Maximum number of weight can be gathered:");
            printf("%d\n", knapsack(0, limitBudget));
            printf("\n Item numbered:");

            int getIteam = 0;
            int rem = limitBudget;

            while (getIteam != knapsackItemNumber)
            {

                if (choice[getIteam][rem] == 0)
                {

                    getIteam++;
                }
                else
                {

                    printf("%d, ", getIteam + 1);
                    rem -= b[getIteam].budget;
                    getIteam++;
                }
            }
            printf("should be taken\n");
            break;
        }
        case 3:
        {
            {
                cout << "Thanks For viewing Our Small Project" << endl;
                cout << "Regards from," << endl
                     << endl
                     << " Rafsan Bari Shafin && Marwa Khanom Nurtaj && Nahid Hasan" << endl;
                exit(0);
            }
        }

        default:
            cout << " Please select a valid number" << endl;
            break;
        }
    }
}
