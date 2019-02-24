#include <fstream>
#define MaxN 1003
#define MOD 1000000
using namespace std;
ifstream in("sir23.in");
ofstream out("sir23.out");

int n;
int A[MaxN][MaxN];
int V[] = {1,4,9,31,88,288,889,2884,9211,29976,97296,318371,42756,429604,298969,320679,473176,243756,333979,751168,722088,271044,787424,286656,8543,340768,713852,732667,391128,567444,548569,908292,494227,537808,793808,807133,463736,577996,666139,107464,399424,713976,18056,547504,349748,279968,216064,919419,654836,120876,59551,751604,678784,482756,184908,133908,799879,494224,812496,347851,713736,716004,423769,481671,101016,199356,271859,631904,905536,257972,624352,123996,620241,137104,44544,656969,266376,124396,539739,312992,695592,65456,718336,88344,884344,488224,930824,177364,598176,567376,27316,555584,843104,513936,730752,146432,283271,83616,246604,251033,326408,65772,414687,146608,835364,671864,390592,901652,492708,260528,277228,129331,415416,677644,563559,330144,25536,411316,162144,533508,622103,373744,250624,983531,916568,932068,414297,827012,636083,860784,786384,432277,14312,959148,907443,40928,235648,97528,861152,492272,889252,967488,102528,736277,55384,869844,506097,608912,444128,996684,823984,333276,340621,920464,74672,235297,45896,69676,154779,36104,971904,926208,288488,649792,110192,975072,529728,466968,218712,374944,522104,26392,560832,847808,177608,265008,548132,699072,293248,604364,320864,511632,27892,766368,839808,260448,711264,93504,947536,395456,72896,624219,816564,646476,381127,787332,310336,908756,996764,478364,33789,151856,636976,846709,836152,920252,278111,6516,796064,683264,201444,885024,639064,668976,282176,76116,67284,180304,911236,523652,28832,874496,388716,2004,448463,767088,848592,736657,262088,985404,610279,706912,115072,712888,247008,765808,662436,357696,977664,832579,711464,136716,953271,162864,572448,289268,66064,397844,326711,451376,535376,310379,959384,453156,244313,192263,845464,721084,61011,218976,787296,817396,570656,604204,809769,857104,473776,834481,594504,486668,990963,634944,345824,46256,137088,226688,252632,444672,558048,488004,481504,136272,645732,203328,198528,805328,578496,115356,119129,132304,828864,901111,106616,299044,799153,136448,161904,434184,682496,267776,722076,931904,733584,320081,266408,219908,611629,608224,854496,487676,883296,783996,110981,586704,393584,724369,780616,569196,675739,740128,686248,751104,481984,622296,642016,877216,65064,79344,951296,733888,242288,496384,852704,186816,26816,328536,661016,913376,16984,824584,508544,118656,561336,517024,16568,386688,838464,849944,973536,649632,682632,672788,172448,793232,88356,857856,643968,484208,831232,965712,996412,557504,750144,550396,161056,847696,417524,316544,360096,817472,669952,670496,504416,887104,280544,214544,898176,864896,646864,777472,70272,226816,300096,579584,857319,453024,2124,246689,536776,593036,774151,829744,331764,207576,862592,557572,720436,812656,234364,330737,993512,30468,513053,832352,970496,747996,682528,595068,747497,957072,801472,938669,444584,512956,475231,915696,801604,571424,954816,48892,824272,722256,712676,888344,510144,729344,649176,348096,991664,3552,791552,431476,595156,323024,758644,617084,694176,982336,739524,93104,316564,201696,818176,383684,85168,275888,695724,263379,133176,410476,349551,937504,943584,501956,265568,881468,737749,184144,150576,42701,118696,717916,706151,83584,399584,530544,315456,291136,283224,720768,609888,42564,16544,641936,845412,382912,449408,869968,606912,73796,880671,525488,123328,294337,433992,648892,79479,759744,241296,460856,570496,209024,811044,636096,133872,592227,445496,59916,843479,496608,216608,70132,320672,664148,962679,121904,952912,280747,652888,697508,291993,596228,631283,553072,530192,860597,601768,425708,976147,407424,521984,623992,648832,34608,896804,567104,331456,349901,398984,799732,846857,649376,89056,962924,905824,12924,104533,788688,284592,608617,636872,516428,221043,788512,969344,473504,304992,186432,780208,964928,99328,47512,979552,249568,427224,248224,974912,975072,741088,354928,221268,692544,163584,129756,692576,964816,418724,273344,130496,412192,335872,219456,141776,110144,128384,848309,699736,371956,809529,328912,484512,586716,222896,666084,791059,706864,328464,662779,384536,208836,10801,613424,998144,161296,501872,40352,546856,435776,854144,429948,682448,803632,337372,561648,526784,884784,772752,979612,207173,897168,857968,299131,776216,357844,38509,521344,974336,208616,225344,848208,476428,199744,266624,702281,78568,156068,279397,134112,88608,915484,751584,235452,29237,808848,120368,976753,688328,422508,568347,254792,667072,265568,828008,401472,900224,34784,811392,783232,17208,612224,621024,126136,717056,825504,663592,622592,859056,891136,95744,169744,89344,502848,340528,901152,802752,444032,715168,956608,769472,307264,108224,774552,399192,311648,431768,824168,319872,954112,923608,845344,562344,699072,396032,749928,537568,559648,39352,507672,666048,957408,126328,238592,687552,987168,489536,710976,430648,710208,621152,622872,886272,573088,363848,250032,517796,844096,368128,59068,226272,960272,514212,184512,740032,507488,833088,7808,889392,201152,818368,733676,546016,364848,67708,969152,341504,39504,398336,995856,954604,232832,784832,555996,63776,341904,448564,461664,742528,347008,186272,297792,526272,45568,846208,242272,31904,251264,991072,388512,144128,296384,780384,492736,448656,504704,80192,42992,430976,813056,289424,216384,880064,260224,537664,178176,524736,350976,598144,424539,186676,330892,454247,592836,29056,546964,419292,501692,659813,576048,128432,754061,850936,358748,800263,75652,102752,1152,527604,883744,627896,730096,417536,811364,52484,907856,133972,120052,321696,436416,25404,495004,321829,393616,36336,694699,635032,704532,171741,414496,80384,680104,16224,723792,988012,572608,754368,894813,435032,592692,564553,458256,342496,986508,326768,257292,502017,115792,526768,364253,72552,183356,200031,921908,1248,494992,969092,581632,842272,41392,129728,163328,207148,743552,136112,370508,689056,806096,634788,948448,94712,902464,606464,833576,996896,890464,532312,771312,233536,902016,530864,172224,750624,596608,717888,188692,933812,256592,624948,842988,597792,775744,937204,917392,26732,347808,788608,488108,460432,155472,841348,184804,535904,396112,535572,410688,245408,1968,466368,104448,838932,813952,359632,715908,790048,518832,246444,454804,807727,561392,151248,191929,308104,948956,95151,849984,112832,815832,440576,678256,668724,613824,524224,605993,254248,988132,383157,636512,216288,944828,761952,694924,989409,18832,529072,119493,28008,354908,64807,427872,888448,381664,469664,847232,330992,16768,475008,136408,288736,878496,437464,600544,391104,274656,315936,551024,764948,146368,676864,12444,997536,629456,845156,717824,122304,675936,583808,78208,60944,776064,960256,252131,292776,186156,249791,879344,142944,332804,458896,761276,247109,510288,780208,73149,865704,984476,861687,15312,41408,961968,776912,235296,462296,924288,232128,841412,996592,843792,256164,581904,372736,929296,151536,806484,655679,565936,382352,554657,387336,770556,543639,332864};

int main()
{
    int i, j, l;
    in >> n;
    out << V[n - 1];

    /*A[1][1] = A[1][2] = 1;
    for(i = 1; i <= n ; ++i)
    {
        A[i][1] = i, A[i][2] = i * i;
        for(j = 3; j <= 2 * i ; ++j)
        {
            for(l = 1; l < i ; ++l)
                A[i][j] = (A[i][j] + A[i - l][j - 1]) % MOD;
            for(l = 1; l < i ; ++l)
                A[i][j] = (A[i][j] + l * A[i - l][j - 2]) % MOD;
        }
        A[i][j] %= MOD;

    }

    out << "V[] = {";
    for(i = 1; i <= n ; ++i)
        out << A[i][i] << ",";
    out << "}";

    /*for(i = 1; i <= n ; ++i)
    {
        for(j = 1; j <= 2 * n ; ++j)
            out << A[i][j] << " ";
        out << "\n";
    }*/
    return 0;
}