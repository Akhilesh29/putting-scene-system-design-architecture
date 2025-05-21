# Putting Scene - Event Discovery Platform

## 🏗️ System Architecture

### High-Level Design (HLD)

```
┌─────────────────────────────────────────────────────────────────────────┐
│                           Client Applications                            │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐    │
│  │  Web App    │  │ Mobile App  │  │  Admin UI   │  │  API Users  │    │
│  └─────────────┘  └─────────────┘  └─────────────┘  └─────────────┘    │
└───────────────────────────┬─────────────────────────────────────────────┘
                            │
                            ▼
┌─────────────────────────────────────────────────────────────────────────┐
│                           API Gateway Layer                             │
│  ┌─────────────────────────────────────────────────────────────────┐    │
│  │  • Request Routing                                             │    │
│  │  • Rate Limiting                                              │    │
│  │  • Authentication/Authorization                               │    │
│  │  • Request/Response Transformation                            │    │
│  └─────────────────────────────────────────────────────────────────┘    │
└───────────────────────────┬─────────────────────────────────────────────┘
                            │
                            ▼
┌─────────────────────────────────────────────────────────────────────────┐
│                        Core Service Layer                               │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐    │
│  │ Event       │  │ Venue       │  │ User        │  │ Search      │    │
│  │ Service     │◄─┤ Service     │◄─┤ Service     │◄─┤ Service     │    │
│  └─────┬───────┘  └─────┬───────┘  └─────┬───────┘  └─────┬───────┘    │
└────────┼────────────────┼────────────────┼────────────────┼────────────┘
         │                │                │                │
         ▼                ▼                ▼                ▼
┌─────────────────────────────────────────────────────────────────────────┐
│                        Data Access Layer                                │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐    │
│  │ PostgreSQL  │  │ Redis Cache │  │ Elastic     │  │ File        │    │
│  │ Database    │  │ Layer       │  │ Search      │  │ Storage     │    │
│  └─────────────┘  └─────────────┘  └─────────────┘  └─────────────┘    │
└─────────────────────────────────────────────────────────────────────────┘
```

## 🚀 Key Features

### 1. Multi-Level Caching System
```
┌─────────────────────────────────────────────────────────┐
│                     Caching Strategy                     │
├─────────────────────────────────────────────────────────┤
│  L1: In-Memory Cache (Fastest)                          │
│  L2: Redis Cache (Distributed)                          │
│  L3: Database (Persistent)                              │
└─────────────────────────────────────────────────────────┘
```

### 2. Search Architecture
```
┌─────────────────────────────────────────────────────────┐
│                     Search Pipeline                      │
├─────────────────────────────────────────────────────────┤
│  1. Query Analysis                                      │
│  2. Multi-Index Search                                  │
│  3. Result Aggregation                                  │
│  4. Response Caching                                    │
└─────────────────────────────────────────────────────────┘
```

### 3. Database Design
```
┌─────────────┐    ┌─────────────┐    ┌─────────────┐
│   Events    │    │   Venues    │    │   Users     │
├─────────────┤    ├─────────────┤    ├─────────────┤
│ id          │    │ id          │    │ id          │
│ title       │    │ name        │    │ email       │
│ description │    │ location    │    │ password    │
│ start_time  │    │ capacity    │    │ role        │
│ end_time    │    │ amenities   │    │ created_at  │
│ venue_id    │    │ created_at  │    │ updated_at  │
│ price       │    │ updated_at  │    └─────────────┘
│ tickets     │    └─────────────┘
└─────────────┘
```

## 🛠️ Technology Stack

- **Backend**: C++17/20
- **Database**: PostgreSQL with PostGIS
- **Caching**: Redis
- **Search**: Elasticsearch
- **API**: gRPC & REST
- **Message Queue**: RabbitMQ
- **Container**: Docker
- **Orchestration**: Kubernetes

## 📊 Performance Optimizations

1. **Caching Strategy**
   - L1 Cache: In-memory cache for frequently accessed data
   - L2 Cache: Redis for distributed caching
   - L3 Cache: Database for persistent storage

2. **Database Optimization**
   - Indexed fields for common queries
   - Partitioned tables for large datasets
   - Connection pooling

3. **Search Optimization**
   - Elasticsearch for full-text search
   - Geospatial indexing for location-based queries
   - Result caching

4. **API Optimization**
   - Response compression
   - Pagination
   - Field filtering

## 🔄 Data Flow

1. **Event Creation Flow**:
```
Client → API Gateway → Event Service → PostgreSQL
                              ↓
                        Redis Cache
```

2. **Search Flow**:
```
Client → API Gateway → Search Service → Elasticsearch
                              ↓
                        Redis Cache
```

3. **User Authentication Flow**:
```
Client → API Gateway → User Service → PostgreSQL
                              ↓
                        Redis Cache
```

## 🏗️ Project Structure

```
putting-scene/
├── CMakeLists.txt
├── README.md
├── config/
│   └── api_gateway.yaml
├── docs/
│   ├── architecture/
│   │   └── block_architecture.md
│   └── database/
│       └── schema.sql
├── include/
│   ├── models/
│   │   ├── Event.hpp
│   │   └── Venue.hpp
│   └── services/
│       └── EventService.hpp
└── src/
    ├── cache/
    │   └── CacheManager.hpp
    └── services/
        └── EventServiceImpl.cpp
```

