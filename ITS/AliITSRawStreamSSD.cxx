/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/* $Id$ */

///////////////////////////////////////////////////////////////////////////////
///
/// This class provides access to ITS SSD digits in raw data.
//  Revised by Enrico Fragiacomo
//  Last update: 2007/09/06
///
///////////////////////////////////////////////////////////////////////////////

#include "Riostream.h"
#include "TGeoManager.h"
#include "TGeoVolume.h"
#include <TClass.h>

#include "AliITSRawStreamSSD.h"
#include "AliRawReader.h"
#include "AliLog.h"

ClassImp(AliITSRawStreamSSD)

Bool_t AliITSRawStreamSSD::fgkDDLModuleMapInit = kFALSE;  
Int_t AliITSRawStreamSSD::fgkDDLModuleMap[kDDLsNumber][kModulesPerDDL] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0}
};

AliITSRawStreamSSD::AliITSRawStreamSSD(AliRawReader* rawReader) :
  AliITSRawStream(rawReader),
  fddl(0),
  fad(0),
  fadc(0),
  flag(0),
  fData(0) {
  // create an object to read ITS SSD raw digits
  
  if(!gGeoManager){
    AliError("Geometry is not initialized\n");
    return;
  }
  TGeoVolume *v = NULL;
  v = gGeoManager->GetVolume("ITSssdSensitivL5");
  if(!v) {
    // new geometry AliITSvPPRasymmFMD
    AliInfo(Form("Enabling the SSD DDL mapping for the AliITSvPPRasymmFMD"));
    SetvPPRasymmFMDDDLMapping();
  }
  else {
    // new geometry AliITSv11Hybrid
    AliInfo(Form("Enabling the SSD DDL mapping for the AliITSv11Hybrid"));
    Setv11HybridDDLMapping();
  }
  //  fRawReader->Reset();
  fRawReader->Select("ITSSSD");
}

Int_t AliITSRawStreamSSD::GetModuleNumber(UInt_t iDDL, UInt_t iModule)
{
  if (!fgkDDLModuleMapInit) {
    if (!InitDDLModuleMap()) return -1;
  }
  return fgkDDLModuleMap[iDDL][iModule];
}

Bool_t AliITSRawStreamSSD::InitDDLModuleMap()
{
  // Initialize the DDL
  // module map
  if(!gGeoManager){
    AliErrorClass("Geometry is not initialized\n");
    return kFALSE;
  }
  TGeoVolume *v = NULL;
  v = gGeoManager->GetVolume("ITSssdSensitivL5");
  if(!v) {
    // new geometry AliITSvPPRasymmFMD
    AliInfoClass(Form("Enabling the SSD DDL mapping for the AliITSvPPRasymmFMD"));
    SetvPPRasymmFMDDDLMapping();
  }
  else {
    // new geometry AliITSv11Hybrid
    AliInfoClass(Form("Enabling the SSD DDL mapping for the AliITSv11Hybrid"));
    Setv11HybridDDLMapping();
  }
  fgkDDLModuleMapInit = kTRUE;
  return kTRUE;
}

void AliITSRawStreamSSD::Setv11HybridDDLMapping() {
  //DDL mapping v11Hybrid
  Int_t kDDLModuleMap[kDDLsNumber][kModulesPerDDL] = {

// ddl0
{753,752,743,742,745,744,747,746,749,748,751,750,775,774,765,764,767,766,769,768,771,770,773,772,797,796,787,786,789,788,791,790,793,792,795,794,1549,1548,1551,1550,1553,1552,1555,1554,1557,1556,1559,1558,1599,1598,1601,1600,1603,1602,1605,1604,1607,1606,1609,1608,1624,1623,1626,1625,1628,1627,1630,1629,1632,1631,1634,1633,731,730,721,720,723,722,725,724,727,726,729,728,1524,1523,1526,1525,1528,1527,1530,1529,1532,1531,1534,1533,1574,1573,1576,1575,1578,1577,1580,1579,1582,1581,1584,1583},

// ddl1
{819,818,809,808,811,810,813,812,815,814,817,816,841,840,831,830,833,832,835,834,837,836,839,838,863,862,853,852,855,854,857,856,859,858,861,860,1649,1648,1651,1650,1653,1652,1655,1654,1657,1656,1659,1658,1674,1673,1676,1675,1678,1677,1680,1679,1682,1681,1684,1683,1724,1723,1726,1725,1728,1727,1730,1729,1732,1731,1734,1733,885,884,875,874,877,876,879,878,881,880,883,882,907,906,897,896,899,898,901,900,903,902,905,904,1699,1698,1701,1700,1703,1702,1705,1704,1707,1706,1709,1708},

// ddl2
{951,950,941,940,943,942,945,944,947,946,949,948,973,972,963,962,965,964,967,966,969,968,971,970,995,994,985,984,987,986,989,988,991,990,993,992,1774,1773,1776,1775,1778,1777,1780,1779,1782,1781,1784,1783,1824,1823,1826,1825,1828,1827,1830,1829,1832,1831,1834,1833,1849,1848,1851,1850,1853,1852,1855,1854,1857,1856,1859,1858,929,928,919,918,921,920,923,922,925,924,927,926,1749,1748,1751,1750,1753,1752,1755,1754,1757,1756,1759,1758,1799,1798,1801,1800,1803,1802,1805,1804,1807,1806,1809,1808},

// ddl3
{1017,1016,1007,1006,1009,1008,1011,1010,1013,1012,1015,1014,1039,1038,1029,1028,1031,1030,1033,1032,1035,1034,1037,1036,1061,1060,1051,1050,1053,1052,1055,1054,1057,1056,1059,1058,1874,1873,1876,1875,1878,1877,1880,1879,1882,1881,1884,1883,1899,1898,1901,1900,1903,1902,1905,1904,1907,1906,1909,1908,1949,1948,1951,1950,1953,1952,1955,1954,1957,1956,1959,1958,1083,1082,1073,1072,1075,1074,1077,1076,1079,1078,1081,1080,1924,1923,1926,1925,1928,1927,1930,1929,1932,1931,1934,1933,1974,1973,1976,1975,1978,1977,1980,1979,1982,1981,1984,1983},

// ddl4
{1127,1126,1117,1116,1119,1118,1121,1120,1123,1122,1125,1124,1149,1148,1139,1138,1141,1140,1143,1142,1145,1144,1147,1146,1171,1170,1161,1160,1163,1162,1165,1164,1167,1166,1169,1168,2024,2023,2026,2025,2028,2027,2030,2029,2032,2031,2034,2033,2074,2073,2076,2075,2078,2077,2080,2079,2082,2081,2084,2083,2099,2098,2101,2100,2103,2102,2105,2104,2107,2106,2109,2108,1105,1104,1095,1094,1097,1096,1099,1098,1101,1100,1103,1102,1999,1998,2001,2000,2003,2002,2005,2004,2007,2006,2009,2008,2049,2048,2051,2050,2053,2052,2055,2054,2057,2056,2059,2058},

// ddl5
{1193,1192,1183,1182,1185,1184,1187,1186,1189,1188,1191,1190,1215,1214,1205,1204,1207,1206,1209,1208,1211,1210,1213,1212,1237,1236,1227,1226,1229,1228,1231,1230,1233,1232,1235,1234,1249,1248,1251,1250,1253,1252,1255,1254,1257,1256,1259,1258,2124,2123,2126,2125,2128,2127,2130,2129,2132,2131,2134,2133,2149,2148,2151,2150,2153,2152,2155,2154,2157,2156,2159,2158,511,510,501,500,503,502,505,504,507,506,509,508,533,532,523,522,525,524,527,526,529,528,531,530,2174,2173,2176,2175,2178,2177,2180,2179,2182,2181,2184,2183},

// ddl6
{577,576,567,566,569,568,571,570,573,572,575,574,599,598,589,588,591,590,593,592,595,594,597,596,621,620,611,610,613,612,615,614,617,616,619,618,1299,1298,1301,1300,1303,1302,1305,1304,1307,1306,1309,1308,1349,1348,1351,1350,1353,1352,1355,1354,1357,1356,1359,1358,1374,1373,1376,1375,1378,1377,1380,1379,1382,1381,1384,1383,555,554,545,544,547,546,549,548,551,550,553,552,1274,1273,1276,1275,1278,1277,1280,1279,1282,1281,1284,1283,1324,1323,1326,1325,1328,1327,1330,1329,1332,1331,1334,1333},

// ddl7
{643,642,633,632,635,634,637,636,639,638,641,640,665,664,655,654,657,656,659,658,661,660,663,662,687,686,677,676,679,678,681,680,683,682,685,684,1399,1398,1401,1400,1403,1402,1405,1404,1407,1406,1409,1408,1424,1423,1426,1425,1428,1427,1430,1429,1432,1431,1434,1433,1474,1473,1476,1475,1478,1477,1480,1479,1482,1481,1484,1483,709,708,699,698,701,700,703,702,705,704,707,706,1449,1448,1451,1450,1453,1452,1455,1454,1457,1456,1459,1458,1499,1498,1501,1500,1503,1502,1505,1504,1507,1506,1509,1508},

// ddl8
{1560,-1,762,763,760,761,758,759,756,757,754,755,1635,-1,784,785,782,783,780,781,778,779,776,777,1610,-1,806,807,804,805,802,803,800,801,798,799,1571,1572,1569,1570,1567,1568,1565,1566,1563,1564,1561,1562,1621,1622,1619,1620,1617,1618,1615,1616,1613,1614,1611,1612,1646,1647,1644,1645,1642,1643,1640,1641,1638,1639,1636,1637,1535,1585,740,741,738,739,736,737,734,735,732,733,1546,1547,1544,1545,1542,1543,1540,1541,1538,1539,1536,1537,1596,1597,1594,1595,1592,1593,1590,1591,1588,1589,1586,1587},

// ddl9
{1685,-1,828,829,826,827,824,825,822,823,820,821,1660,-1,850,851,848,849,846,847,844,845,842,843,1735,-1,872,873,870,871,868,869,866,867,864,865,1671,1672,1669,1670,1667,1668,1665,1666,1663,1664,1661,1662,1696,1697,1694,1695,1692,1693,1690,1691,1688,1689,1686,1687,1746,1747,1744,1745,1742,1743,1740,1741,1738,1739,1736,1737,-1,1710,894,895,892,893,890,891,888,889,886,887,-1,-1,916,917,914,915,912,913,910,911,908,909,1721,1722,1719,1720,1717,1718,1715,1716,1713,1714,1711,1712},

// ddl10
{1785,-1,960,961,958,959,956,957,954,955,952,953,1860,-1,982,983,980,981,978,979,976,977,974,975,1835,-1,1004,1005,1002,1003,1000,1001,998,999,996,997,1796,1797,1794,1795,1792,1793,1790,1791,1788,1789,1786,1787,1846,1847,1844,1845,1842,1843,1840,1841,1838,1839,1836,1837,1871,1872,1869,1870,1867,1868,1865,1866,1863,1864,1861,1862,1760,1810,938,939,936,937,934,935,932,933,930,931,1771,1772,1769,1770,1767,1768,1765,1766,1763,1764,1761,1762,1821,1822,1819,1820,1817,1818,1815,1816,1813,1814,1811,1812},

// ddl11
{1910,-1,1026,1027,1024,1025,1022,1023,1020,1021,1018,1019,1885,-1,1048,1049,1046,1047,1044,1045,1042,1043,1040,1041,1960,-1,1070,1071,1068,1069,1066,1067,1064,1065,1062,1063,1896,1897,1894,1895,1892,1893,1890,1891,1888,1889,1886,1887,1921,1922,1919,1920,1917,1918,1915,1916,1913,1914,1911,1912,1971,1972,1969,1970,1967,1968,1965,1966,1963,1964,1961,1962,1985,1935,1092,1093,1090,1091,1088,1089,1086,1087,1084,1085,1946,1947,1944,1945,1942,1943,1940,1941,1938,1939,1936,1937,1996,1997,1994,1995,1992,1993,1990,1991,1988,1989,1986,1987},

// ddl12
{2035,-1,1136,1137,1134,1135,1132,1133,1130,1131,1128,1129,2110,-1,1158,1159,1156,1157,1154,1155,1152,1153,1150,1151,2085,-1,1180,1181,1178,1179,1176,1177,1174,1175,1172,1173,2046,2047,2044,2045,2042,2043,2040,2041,2038,2039,2036,2037,2096,2097,2094,2095,2092,2093,2090,2091,2088,2089,2086,2087,2121,2122,2119,2120,2117,2118,2115,2116,2113,2114,2111,2112,2010,2060,1114,1115,1112,1113,1110,1111,1108,1109,1106,1107,2021,2022,2019,2020,2017,2018,2015,2016,2013,2014,2011,2012,2071,2072,2069,2070,2067,2068,2065,2066,2063,2064,2061,2062},

// ddl13
{2160,-1,1202,1203,1200,1201,1198,1199,1196,1197,1194,1195,2135,-1,1224,1225,1222,1223,1220,1221,1218,1219,1216,1217,1260,-1,1246,1247,1244,1245,1242,1243,1240,1241,1238,1239,1271,1272,1269,1270,1267,1268,1265,1266,1263,1264,1261,1262,2146,2147,2144,2145,2142,2143,2140,2141,2138,2139,2136,2137,2171,2172,2169,2170,2167,2168,2165,2166,2163,2164,2161,2162,-1,2185,520,521,518,519,516,517,514,515,512,513,-1,-1,542,543,540,541,538,539,536,537,534,535,2196,2197,2194,2195,2192,2193,2190,2191,2188,2189,2186,2187},

// ddl14
{1310,-1,586,587,584,585,582,583,580,581,578,579,1385,-1,608,609,606,607,604,605,602,603,600,601,1360,-1,630,631,628,629,626,627,624,625,622,623,1321,1322,1319,1320,1317,1318,1315,1316,1313,1314,1311,1312,1371,1372,1369,1370,1367,1368,1365,1366,1363,1364,1361,1362,1396,1397,1394,1395,1392,1393,1390,1391,1388,1389,1386,1387,1285,1335,564,565,562,563,560,561,558,559,556,557,1296,1297,1294,1295,1292,1293,1290,1291,1288,1289,1286,1287,1346,1347,1344,1345,1342,1343,1340,1341,1338,1339,1336,1337},

// ddl15
{1435,-1,652,653,650,651,648,649,646,647,644,645,1410,-1,674,675,672,673,670,671,668,669,666,667,1485,-1,696,697,694,695,692,693,690,691,688,689,1421,1422,1419,1420,1417,1418,1415,1416,1413,1414,1411,1412,1446,1447,1444,1445,1442,1443,1440,1441,1438,1439,1436,1437,1496,1497,1494,1495,1492,1493,1490,1491,1488,1489,1486,1487,1510,1460,718,719,716,717,714,715,712,713,710,711,1471,1472,1469,1470,1467,1468,1465,1466,1463,1464,1461,1462,1521,1522,1519,1520,1517,1518,1515,1516,1513,1514,1511,1512}
    
    };
  for(Int_t iddl = 0; iddl < kDDLsNumber; iddl++) {
    for(Int_t imodule = 0; imodule < kModulesPerDDL; imodule++) {
      fgkDDLModuleMap[iddl][imodule] = kDDLModuleMap[iddl][imodule];
    }
  }
}

void AliITSRawStreamSSD::SetvPPRasymmFMDDDLMapping() {
//DDL mapping AliITSvPPRasymmFMD
  Int_t kDDLModuleMap[kDDLsNumber][kModulesPerDDL] = {
    
    // ddl0
    {1214,1215,1224,1225,1222,1223,1220,1221,1218,1219,1216,1217,
     1192,1193,1202,1203,1200,1201,1198,1199,1196,1197,1194,1195,
     1170,1171,1180,1181,1178,1179,1176,1177,1174,1175,1172,1173,
     1148,1149,1158,1159,1156,1157,1154,1155,1152,1153,1150,1151,
     2121,2122,2119,2120,2117,2118,2115,2116,2113,2114,2111,2112,
     2096,2097,2094,2095,2092,2093,2090,2091,2088,2089,2086,2087,
     2071,2072,2069,2070,2067,2068,2065,2066,2063,2064,2061,2062,
     2046,2047,2044,2045,2042,2043,2040,2041,2038,2039,2036,2037,
     2021,2022,2019,2020,2017,2018,2015,2016,2013,2014,2011,2012},
    
    // ddl1
    {1126,1127,1136,1137,1134,1135,1132,1133,1130,1131,1128,1129,
     1104,1105,1114,1115,1112,1113,1110,1111,1108,1109,1106,1107,
     1082,1083,1092,1093,1090,1091,1088,1089,1086,1087,1084,1085,
     1060,1061,1070,1071,1068,1069,1066,1067,1064,1065,1062,1063,
     1038,1039,1048,1049,1046,1047,1044,1045,1042,1043,1040,1041,
     1996,1997,1994,1995,1992,1993,1990,1991,1988,1989,1986,1987,
     1971,1972,1969,1970,1967,1968,1965,1966,1963,1964,1961,1962,
     1946,1947,1944,1945,1942,1943,1940,1941,1938,1939,1936,1937,
     1921,1922,1919,1920,1917,1918,1915,1916,1913,1914,1911,1912},
    
    // ddl2
    {1016,1017,1026,1027,1024,1025,1022,1023,1020,1021,1018,1019,
     994,995,1004,1005,1002,1003,1000,1001,998,999,996,997,
     972,973,982,983,980,981,978,979,976,977,974,975,
     950,951,960,961,958,959,956,957,954,955,952,953,
     1896,1897,1894,1895,1892,1893,1890,1891,1888,1889,1886,1887,
     1871,1872,1869,1870,1867,1868,1865,1866,1863,1864,1861,1862,
     1846,1847,1844,1845,1842,1843,1840,1841,1838,1839,1836,1837,
     1821,1822,1819,1820,1817,1818,1815,1816,1813,1814,1811,1812,
     1796,1797,1794,1795,1792,1793,1790,1791,1788,1789,1786,1787},
    
    // ddl3
    {928,929,938,939,936,937,934,935,932,933,930,931,
     906,907,916,917,914,915,912,913,910,911,908,909,
     884,885,894,895,892,893,890,891,888,889,886,887,
     862,863,872,873,870,871,868,869,866,867,864,865
     ,1771,1772,1769,1770,1767,1768,1765,1766,1763,1764,1761,1762,
     1746,1747,1744,1745,1742,1743,1740,1741,1738,1739,1736,1737,
     1721,1722,1719,1720,1717,1718,1715,1716,1713,1714,1711,1712,
     1696,1697,1694,1695,1692,1693,1690,1691,1688,1689,1686,1687,
     1671,1672,1669,1670,1667,1668,1665,1666,1663,1664,1661,1662},
    
    // ddl4
    {840,841,850,851,848,849,846,847,844,845,842,843,
     818,819,828,829,826,827,824,825,822,823,820,821,
     796,797,806,807,804,805,802,803,800,801,798,799,
     774,775,784,785,782,783,780,781,778,779,776,777,
     1646,1647,1644,1645,1642,1643,1640,1641,1638,1639,1636,1637,
     1621,1622,1619,1620,1617,1618,1615,1616,1613,1614,1611,1612,
     1596,1597,1594,1595,1592,1593,1590,1591,1588,1589,1586,1587,
     1571,1572,1569,1570,1567,1568,1565,1566,1563,1564,1561,1562,
     1546,1547,1544,1545,1542,1543,1540,1541,1538,1539,1536,1537},
    
    // ddl5
    {752,753,762,763,760,761,758,759,756,757,754,755,
     730,731,740,741,738,739,736,737,734,735,732,733,
     708,709,718,719,716,717,714,715,712,713,710,711,
     686,687,696,697,694,695,692,693,690,691,688,689,
     664,665,674,675,672,673,670,671,668,669,666,667,
     1521,1522,1519,1520,1517,1518,1515,1516,1513,1514,1511,1512,
     1496,1497,1494,1495,1492,1493,1490,1491,1488,1489,1486,1487,
     1471,1472,1469,1470,1467,1468,1465,1466,1463,1464,1461,1462,
     1446,1447,1444,1445,1442,1443,1440,1441,1438,1439,1436,1437},
    
    // ddl6
    {642,643,652,653,650,651,648,649,646,647,644,645,
     620,621,630,631,628,629,626,627,624,625,622,623,
     598,599,608,609,606,607,604,605,602,603,600,601,
     576,577,586,587,584,585,582,583,580,581,578,579,
     1421,1422,1419,1420,1417,1418,1415,1416,1413,1414,1411,1412,
     1396,1397,1394,1395,1392,1393,1390,1391,1388,1389,1386,1387,
     1369,1371,1365,1367,1361,1363,1357,1359,1353,1355,1349,1351,
     1346,1347,1344,1345,1342,1343,1340,1341,1338,1339,1336,1337,
     1321,1322,1319,1320,1317,1318,1315,1316,1313,1314,1311,1312},
    
    // ddl7
    {554,555,564,565,562,563,560,561,558,559,556,557,
     532,533,542,543,540,541,538,539,536,537,534,535,
     510,511,520,521,518,519,516,517,514,515,512,513,
     1236,1237,1246,1247,1244,1245,1242,1243,1240,1241,1238,1239,
     1296,1297,1294,1295,1292,1293,1290,1291,1288,1289,1286,1287,
     1271,1272,1269,1270,1267,1268,1265,1266,1263,1264,1261,1262,
     2196,2197,2194,2195,2192,2193,2190,2191,2188,2189,2186,2187,
     2171,2172,2169,2170,2167,2168,2165,2166,2163,2164,2161,2162,
     2146,2147,2144,2145,2142,2143,2140,2141,2138,2139,2136,2137},
    
    // ddl8
    {2085,-1,1183,1182,1184,1185,1187,1186,1189,1188,1191,1190,
     2010,-1,1161,1160,1162,1163,1165,1164,1167,1166,1169,1168,
     2035,-1,1139,1138,1140,1141,1143,1142,1145,1144,1147,1146,
     2074,2073,2076,2075,2078,2077,2080,2079,2082,2081,2084,2083,
     2024,2023,2026,2025,2028,2027,2030,2029,2032,2031,2034,2033,
     1999,1998,2001,2000,2003,2002,2005,2004,2007,2006,2009,2008,
     2110,2060,1205,1204,1206,1207,1209,1208,1211,1210,1213,1212,
     2099,2098,2101,2100,2103,2102,2105,2104,2107,2106,2109,2108,
     2049,2048,2051,2050,2053,2052,2055,2054,2057,2056,2059,2058},
    
    // ddl9
    {1960,-1,1117,1116,1118,1119,1121,1120,1123,1122,1125,1124,
     1985,-1,1095,1094,1096,1097,1099,1098,1101,1100,1103,1102,
     1910,-1,1073,1072,1074,1075,1077,1076,1079,1078,1081,1080,
     1974,1973,1976,1975,1978,1977,1980,1979,1982,1981,1984,1983,
     1949,1948,1951,1950,1953,1952,1955,1954,1957,1956,1959,1958,
     1899,1898,1901,1900,1903,1902,1905,1904,1907,1906,1909,1908,
     -1,1935,1051,1050,1052,1053,1055,1054,1057,1056,1059,1058,
     -1,-1,1029,1028,1030,1031,1033,1032,1035,1034,1037,1036,
     1924,1923,1926,1925,1928,1927,1930,1929,1932,1931,1934,1933},
    
    // ddl10
    {1860,-1,985,984,986,987,989,988,991,990,993,992,
     1785,-1,963,962,964,965,967,966,969,968,971,970,
     1810,-1,941,940,942,943,945,944,947,946,949,948,
     1849,1848,1851,1850,1853,1852,1855,1854,1857,1856,1859,1858,
     1799,1798,1801,1800,1803,1802,1805,1804,1807,1806,1809,1808,
     1774,1773,1776,1775,1778,1777,1780,1779,1782,1781,1784,1783,
     1885,1835,1007,1006,1008,1009,1011,1010,1013,1012,1015,1014,
     1874,1873,1876,1875,1878,1877,1880,1879,1882,1881,1884,1883,
     1824,1823,1826,1825,1828,1827,1830,1829,1832,1831,1834,1833},
    
    // ddl11
    {1735,-1,919,918,920,921,923,922,925,924,927,926,
     1760,-1,897,896,898,899,901,900,903,902,905,904,
     1685,-1,875,874,876,877,879,878,881,880,883,882,
     1749,1748,1751,1750,1753,1752,1755,1754,1757,1756,1759,1758,
     1724,1723,1726,1725,1728,1727,1730,1729,1732,1731,1734,1733,
     1674,1673,1676,1675,1678,1677,1680,1679,1682,1681,1684,1683,
     1660,1710,853,852,854,855,857,856,859,858,861,860,
     1699,1698,1701,1700,1703,1702,1705,1704,1707,1706,1709,1708,
     1649,1648,1651,1650,1653,1652,1655,1654,1657,1656,1659,1658},
    
    // ddl12
    {1610,-1,809,808,810,811,813,812,815,814,817,816,
     1535,-1,787,786,788,789,791,790,793,792,795,794,
     1560,-1,765,764,766,767,769,768,771,770,773,772,
     1599,1598,1601,1600,1603,1602,1605,1604,1607,1606,1609,1608,
     1549,1548,1551,1550,1553,1552,1555,1554,1557,1556,1559,1558,
     1524,1523,1526,1525,1528,1527,1530,1529,1532,1531,1534,1533,
     1635,1585,831,830,832,833,835,834,837,836,839,838,
     1624,1623,1626,1625,1628,1627,1630,1629,1632,1631,1634,1633,
     1574,1573,1576,1575,1578,1577,1580,1579,1582,1581,1584,1583},
    
    // ddl13
    {1485,-1,743,742,744,745,747,746,749,748,751,750,
     1510,-1,721,720,722,723,725,724,727,726,729,728,
     1435,-1,699,698,700,701,703,702,705,704,707,706,
     1424,1423,1426,1425,1428,1427,1430,1429,1432,1431,1434,1433,
     1499,1498,1501,1500,1503,1502,1505,1504,1507,1506,1509,1508,
     1474,1473,1476,1475,1478,1477,1480,1479,1482,1481,1484,1483,
     -1,1460,677,676,678,679,681,680,683,682,685,684,
     -1,-1,655,654,656,657,659,658,661,660,663,662,
     1449,1448,1451,1450,1453,1452,1455,1454,1457,1456,1459,1458},
    
    // ddl14
    {1385,-1,611,610,612,613,615,614,617,616,619,618,
     1310,-1,589,588,590,591,593,592,595,594,597,596,
     1335,-1,567,566,568,569,571,570,573,572,575,574,
     1374,1373,1376,1375,1378,1377,1380,1379,1382,1381,1384,1383,
     1324,1323,1326,1325,1328,1327,1330,1329,1332,1331,1334,1333,
     1299,1298,1301,1300,1303,1302,1305,1304,1307,1306,1309,1308,
     1410,1372,633,632,634,635,637,636,639,638,641,640,
     1399,1398,1401,1400,1403,1402,1405,1404,1407,1406,1409,1408,
     1350,1348,1354,1352,1358,1356,1362,1360,1366,1364,1370,1368},
    
    // ddl15
    {1260,-1,545,544,546,547,549,548,551,550,553,552,
     1285,-1,523,522,524,525,527,526,529,528,531,530,
     2160,-1,501,500,502,503,505,504,507,506,509,508,
     1274,1273,1276,1275,1278,1277,1280,1279,1282,1281,1284,1283,
     1249,1248,1251,1250,1253,1252,1255,1254,1257,1256,1259,1258,
     2149,2148,2151,2150,2153,2152,2155,2154,2157,2156,2159,2158,
     2135,2185,1227,1226,1228,1229,1231,1230,1233,1232,1235,1234,
     2174,2173,2176,2175,2178,2177,2180,2179,2182,2181,2184,2183,
     2124,2123,2126,2125,2128,2127,2130,2129,2132,2131,2134,2133}
    
  };

  for(Int_t iddl = 0; iddl < kDDLsNumber; iddl++) {
    for(Int_t imodule = 0; imodule < kModulesPerDDL; imodule++) {
      fgkDDLModuleMap[iddl][imodule] = kDDLModuleMap[iddl][imodule];
    }
  }
}

Bool_t AliITSRawStreamSSD::Next()
{
  // read the next raw digit
  // returns kFALSE if there is no digit left

  flag=0;
  fPrevModuleID = fModuleID;
  if (!fRawReader->ReadNextInt(fData)) return kFALSE;
  
  // new coding following IGF Memo - M.Rossewij - 22-06-2004
  fSignal = (fData & 0x00000FFF); // signal coded in the first 12 bits 
  fSignal  = (fSignal > 2048) ? fSignal - 4096 : fSignal;
		
  UInt_t slot = (fData >> 28) & 0x0000000F;  // slot range 1 - 9
  UInt_t adc =  (fData >> 24) & 0x0000000F;  // adc range 0 - 5 AND 8 - 13;
  UInt_t relModuleID = (slot-1) * 12;        // 0 - 96
  relModuleID += (adc<6) ? adc : (adc-2);   // adds 0 - 5 AND 6 - 11



  flag=1;
  // relModuleID range 0 - 108
  if(relModuleID > kModulesPerDDL){
    fRawReader->AddMajorErrorLog(kWrongModuleIdErr,Form("Module ID = %d > %d (max)",relModuleID,kModulesPerDDL));
    AliWarning(Form("Module ID = %d > %d (max)",relModuleID,kModulesPerDDL));
    return kFALSE;
  }
  flag=0;



  fModuleID = fgkDDLModuleMap[fRawReader->GetDDLID()][relModuleID];
      
  fCoord2 =  (fData >> 12) & 0x000007FF; 
  fCoord1 = (fCoord2 < 768) ? 0 : 1; // strip 0 - 767 are Pside, strip 768 - 1535 are Nside
  fCoord2 = (fCoord1 == 0) ? fCoord2 : (1535 - fCoord2);

  /*
  cout<<"AliITSRawStreamSSD baseword="<<fData<<" slot="<<slot<<" adc="<<adc
      <<" relModuleID="<<relModuleID<<" ddl="<<fRawReader->GetDDLID()
      <<" coord1="<<fCoord1<<" coord2="<<fCoord2<<" signal"<<fSignal
      <<" fModuleID="<<fModuleID<<endl;
  */

  fadc=adc;
  fad=slot;
  fddl=fRawReader->GetDDLID();
  
  return kTRUE;
}

