# Ayanami TODO list

* LICENSE
* LimitOrderBook
* TradeSeries
* Other classes common to exchanges?
* Market absctractclass containing all market objects, such as TradeSeries, LimitOrderbook, Liquidations, etc.
* Exchange abstract class that contains all markets on an exchange

#
## Structure Plan

* Exchange - an Exchange 
    * Enums - enums belonging to the exchange (Exchanges have different names for the same thing or may not offer the same assets, etc.)
    * markets - maximum of one per tradeable asset on the exchange
        * LOB
        * TradeSeries
        * Liquidations
        * Positions
        * Orders
    * wsAPI - updates market objects
    * httpAPI - mainly used for placing orders